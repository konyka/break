# Plugins / RigLogicModule

- module root: `Plugins/Animation/RigLogic/Source/RigLogicModule`
- headers: 24; symbols: 1930
- symbol kinds: class=28, delegate=30, enum=31, enumerator=106, function=402, macro=11, member=165, namespace=5, prototype=1114, struct=36, typedef=2
- PrivateDependencyModuleNames: AnimGraphRuntime, AnimationCore, AssetRegistry, RHI, RenderCore, SkeletalMeshUtilitiesCommon
- PublicDependencyModuleNames: ControlRig, Core, CoreUObject, EditorFramework, Engine, MessageLog, Projects, RigLogicLib, RigVM, UnrealEd

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Private/DNAAssetCustomVersion.h` (Private)


#### struct `FDNAAssetCustomVersion`  
`struct FDNAAssetCustomVersion`  
_L9-29_
- desc: Custom serialization version for all packages containing DNAAsset types
- L25 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L28 _private function_ `FDNAAssetCustomVersion()`

#### enum `FDNAAssetCustomVersion::Type`  
`enum Type`  
_L11-22_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L15 _public enumerator_ `UnifiedReaderVersion`
- L16 _public enumerator_ `IntroduceOptimizedSerializationDuringCooking`
- L17 _public enumerator_ `GeneralizedCoordinateSystemConversion`
- L18 _public enumerator_ `UserModifiableDNAConfig`
- L20 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L21 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Private/DNAIndexMappingDeprecated.h` (Private)


#### class `UDEPRECATED_DNAIndexMapping`  
`class UDEPRECATED_DNAIndexMapping : public UAssetUserData`  
_L12-15_
- reflection: `UCLASS(NotBlueprintable, hidecategories = (Object), deprecated)`
- inherits: `UAssetUserData`
- desc: Used and needed for previously serialized skeletal mesh assets that contain the DNA index mapping as part of their user data.

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Private/Hasher.h` (Private)


#### class `Hasher`  
`class Hasher`  
_L4-41_
- L7 _public function_ `explicit Hasher(uint32 InitialValue = 0ul) : HashedValue`
- L10 _public function_ `uint32 GetHash() const`
- L14 _public function_ `void Update(const FString& Value)`
- L20 _public function_ `template <typename T> void Update(T Value)`
- L25 _public function_ `template <typename T> void Update(TArrayView<T> Values)`
- L30 _private function_ `void Update(const char* Bytes, size_t Length)`
- L40 _private member_ `uint32 HashedValue;`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Private/LegacyDNAAssetUtils.h` (Private)


#### Free symbols / members of external scopes

- L6 _prototype_ `bool IsLegacyDNAAsset(const dna::Reader* DNAReader);`
- L7 _prototype_ `dna::ScopedPtr<dna::BinaryStreamReader> MigrateLegacyDNAAsset(dna::BoundedIOStream* Stream, const dna::Configuration& DNAConfig);`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Private/RigLogicMemoryStream.h` (Private)


#### class `FRigLogicMemoryStream`  
`class FRigLogicMemoryStream: public rl4::BoundedIOStream`  
_L12-34_
- inherits: `rl4::BoundedIOStream`
- L16 _public prototype_ `explicit FRigLogicMemoryStream(TArray<uint8>* Buffer);` — The buffer is not copied, the pointer to it is stored inside this object
- L18 _public prototype_ `void seek(std::uint64_t Position) override;`
- L19 _public prototype_ `std::uint64_t tell() override;`
- L20 _public prototype_ `void open() override;`
- L21 _public function_ `void close() override`
- L22 _public prototype_ `size_t read(char* ReadToBuffer, size_t Size) override;`
- L23 _public prototype_ `size_t read(Writable* Destination, size_t Size) override;`
- L24 _public prototype_ `size_t write(const char* WriteFromBuffer, size_t Size) override;`
- L25 _public prototype_ `size_t write(Readable* Source, size_t Size) override;`
- L26 _public prototype_ `std::uint64_t size() override;`
- L29 _private prototype_ `void Grow(size_t NewSize);`
- L32 _private member_ `TArray<uint8>* BitStreamBuffer;` — doesn't contain the array, only points to the array given to it
- L33 _private member_ `size_t PositionInBuffer = 0;`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/AnimNode_RigLogic.h` (Public)


#### struct `FAnimNode_RigLogic`  
`struct FAnimNode_RigLogic : public FAnimNode_Base`  
_L22-121_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L27 _public prototype_ `FAnimNode_RigLogic();`
- L28 _public prototype_ `~FAnimNode_RigLogic();`
- L30 _public prototype_ `void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L31 _public prototype_ `void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L32 _public prototype_ `void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L33 _public prototype_ `void Evaluate_AnyThread(FPoseContext& Output) override;`
- L34 _public prototype_ `void GatherDebugData(FNodeDebugData& DebugData) override;`
- L35 _public function_ `int32 GetLODThreshold() const override`
- L39 _public member_ `FPoseLink AnimSequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)`
- L48 _public member_ `bool CacheAnimCurveNames = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RigLogic)` — Since the order of anim curves may change even on a frame by frame basis, it is not safe to cache and rely on cached indices by default, but if the blueprints feeding anim curves into RigLogic are set up in a controlled manner, such that no such runtime changes are expected to the order or number of anim curves, caching may improve the performance of the node, especially in low-LOD evaluations.
- L51 _private typedef_ `using FCachedIndexedCurve = TBaseBlendedCurve<FDefaultAllocator, UE::Anim::FCurveElementIndexed>;`
- L54 _private prototype_ `void CacheVariableJointAttributes(const FBoneContainer& RequiredBones);`
- L55 _private prototype_ `void CacheDriverJoints(const FBoneContainer& RequiredBones);`
- L56 _private prototype_ `void CachePoseCurvesToRigLogicControlsMap(const FPoseContext& InputContext, const FCachedIndexedCurve& IndexedCurves, TArray<int32>& Indices);`
- L57 _private prototype_ `void UpdateRawControls(const FPoseContext& InputContext);`
- L58 _private prototype_ `void UpdateRawControlsCached(const FPoseContext& InputContext);`
- L59 _private prototype_ `void UpdateSparseDriverJointDrivenControlCurves(const FPoseContext& InputContext);`
- L60 _private prototype_ `void UpdateDenseDriverJointDrivenControlCurves(const FPoseContext& InputContext);`
- L61 _private prototype_ `void UpdateMLMaskCurves(const FPoseContext& InputContext);`
- L62 _private prototype_ `void UpdateMLMaskCurvesCached(const FPoseContext& InputContext);`
- L63 _private prototype_ `void UpdateControlCurves(const FPoseContext& InputContext);`
- L64 _private prototype_ `void CalculateRigLogic();`
- L65 _private prototype_ `void UpdateJoints(FPoseContext& OutputContext);`
- L66 _private prototype_ `void UpdateBlendShapeCurves(FPoseContext& OutputContext);`
- L67 _private prototype_ `void UpdateAnimMapCurves(FPoseContext& OutputContext);`
- L113 _private member_ `int32 LODThreshold = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = RigLogic, meta = (PinHiddenByDefault))` — Max LOD level that RigLogic Node is evaluated. For example if you have the threshold set to 2, it will evaluate until including LOD 2 (based on 0 index). In case the LOD level gets set to 3, it will stop evaluating the Rig Logic. Setting it to -1 will always evaluate it.
- L116 _private member_ `TSharedPtr<FSharedRigRuntimeContext> LocalRigRuntimeContext;`
- L117 _private member_ `TSharedPtr<FDNAIndexMapping> LocalDNAIndexMapping;`
- L118 _private member_ `FRigInstance* RigInstance;`
- L119 _private member_ `TArray<FCachedJointMapping> LocalJointMappingsPerLOD;`
- L120 _private member_ `TArray<FCurveElementControlAttributeMapping> PoseCurvesToRigLogicControlsMap;`

#### struct `FAnimNode_RigLogic::FJointCompactPoseBoneMapping`  
`struct FJointCompactPoseBoneMapping`  
_L70-74_
- L72 _public member_ `uint16 JointIndex;`
- L73 _public member_ `FCompactPoseBoneIndex CompactPoseBoneIndex;`

#### struct `FAnimNode_RigLogic::FCompactPoseBoneControlAttributeMapping`  
`struct FCompactPoseBoneControlAttributeMapping`  
_L76-84_
- L78 _public member_ `FCompactPoseBoneIndex CompactPoseBoneIndex;`
- L79 _public member_ `int32 DNAJointIndex;`
- L80 _public member_ `int32 RotationX;`
- L81 _public member_ `int32 RotationY;`
- L82 _public member_ `int32 RotationZ;`
- L83 _public member_ `int32 RotationW;`

#### struct `FAnimNode_RigLogic::FCachedJointMapping`  
`struct FCachedJointMapping`  
_L86-92_
- L88 _public member_ `TArray<FJointCompactPoseBoneMapping> JointsMapDNAIndicesToCompactPoseBoneIndices;`
- L89 _public member_ `TArray<FCompactPoseBoneControlAttributeMapping> SparseDriverJointsToControlAttributesMap;`
- L90 _public member_ `TArray<FCompactPoseBoneControlAttributeMapping> DenseDriverJointsToControlAttributesMap;`
- L91 _public member_ `int32 BoneCount = -1;`

#### struct `FAnimNode_RigLogic::TArrayWrapper`  
`template <typename T> struct TArrayWrapper`  
_L95-98_
- L97 _public member_ `TArray<T> Values;`

#### struct `FAnimNode_RigLogic::FCurveElementControlAttributeMapping`  
`struct FCurveElementControlAttributeMapping`  
_L100-104_
- L102 _public member_ `TArray<int32> RawControlIndices;`
- L103 _public member_ `TArray<int32> MLMaskCurveIndices;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGLOGICMODULE_API`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicAnimNode, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicAnimNode, Log, All);`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/DNA.h` (Public)


#### class `UDNA`  
`class UDNA : public UObject`  
_L42-185_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "DNA"))`
- inherits: `UObject`
- desc: An asset holding the data needed to generate/update/animate a RigLogic character It is imported from character's DNA file as a bit stream, and separated out it into runtime (behavior) and design-time chunks; Currently, the design-time part still loads the geometry, as it is needed for the skeletal mesh update; once SkeletalMeshDNAReader is fully implemented, it will be able to read the geometry directly from the SkeletalMesh and won't load it into this asset
- L47 _public prototype_ `UDNA();`
- L48 _public prototype_ `~UDNA();`
- L52 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = ImportSettings)`
- L55 _public prototype_ `TSharedPtr<IDNAReader> GetDNAReader();`
- L58 _public member_ `FDNAConfig DNAConfig;` — `UPROPERTY(EditAnywhere, Category = "DNA")`
- L66 _public member_ `bool bKeepDNAAfterInitialization;` — `UPROPERTY(EditAnywhere, Category = RuntimeSettings)` — In non-editor builds, the DNA source data will be unloaded to save memory after the runtime data has been initialized from it. Set this property to true to keep the DNA in memory, e.g. if you need to modify it at runtime. For most use cases, this shouldn't be needed.
- L72 _public member_ `bool bUseOptimizedCooking = true;` — `UPROPERTY(EditAnywhere, Category = RuntimeSettings)` — Instead of serializing the DNA data and initialize RigLogic from it in runtime, dump the RigLogic state directly into the cooked asset, skipping the expensive initialization at runtime entirely.
- L78 _public member_ `TMap<FString, FString> MetaData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RuntimeSettings)` — Collection of runtime metadata related to a specific character. The value field is a FString and requires casting for a derived types.
- L81 _public member_ `FRigLogicConfiguration RigLogicConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RuntimeSettings)`
- L84 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L88 _public prototype_ `bool Init(const FString& Filename);` — `UE_DEPRECATED(5.8, "This function has been deprecated, use the overload that also accepts a DNAConfig.")`
- L89 _public prototype_ `bool Init(const FString& Filename, const FDNAConfig& InDNAConfig);`
- L90 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L91 _public prototype_ `void PreSave(FObjectPreSaveContext SaveContext);`
- L92 _public prototype_ `void PostLoad() override;`
- L103 _public prototype_ `void SetDNAReader(TSharedPtr<IDNAReader> SourceDNAReader, EDNACopyPolicy CopyPolicy = EDNACopyPolicy::Copy, ERigLogicInitPolicy InitPolicy = ERigLogicInitPolicy::Initialize);` — Alias or Copy DNA Reader and optionally reinitialize RigLogic with the new DNA data. Pass EDNACopyPolicy::Alias to prevent creation of a deep-copy of the given DNA and instead just take the given shared pointer as-is. Pass ERigLogicInitPolicy::Defer when this call is immediately followed by another operation that rebuilds the runtime context (e.g. RestoreLegacyUEMHCCompatibility) to avoid constructing an FRigLogic that will be thrown away.
- L119 _public prototype_ `void InitializeForRuntimeFrom(UDNA* Other);` — Initialize this object for use at runtime from another instance that has already been initialized. Overwrites all member variables. Only data needed for runtime evaluation will be copied. Performs a shallow copy, so the runtime data is shared between the two instances and the memory cost of the copied UDNA is very low. Note that the reference to the shared runtime data will be dropped if the source DNA is modified, so the two instances are effectively independent and can safely be modified or deleted without affecting the other.
- L120 _public prototype_ `TSharedPtr<FSharedRigRuntimeContext> GetRigRuntimeContext();`
- L121 _public prototype_ `TSharedPtr<FDNAIndexMapping> GetDNAIndexMapping(const USkeleton* Skeleton, const USkeletalMesh* SkeletalMesh);`
- L127 _public prototype_ `void RestoreLegacyUEMHCCompatibility();` — Fallback for users who have not updated to the new conversion workflow. Converts DNA reader data back to its original source space (Maya coordinate space) and provides RigLogic with the same transformed data as in the legacy pipeline.
- L133 _private prototype_ `void InvalidateRigRuntimeContext();`
- L134 _private prototype_ `void InitializeRigRuntimeContext(TSharedPtr<IDNAReader> ReaderForRigLogic);`
- L150 _private function_ `friend uint32 GetTypeHash(const FSkeletalMeshSkeletonToDNAIndexMappingKey& Instance)`
- L158 _private member_ `FTransactionallySafeRWLock DNAUpdateLock;` — Synchronize DNA updates
- L161 _private member_ `FTransactionallySafeRWLock RigRuntimeContextUpdateLock;` — Synchronize Rig Runtime Context updates
- L164 _private member_ `FTransactionallySafeRWLock DNAIndexMappingUpdateLock;` — Synchronize DNA Index Mapping updates
- L167 _private member_ `TSharedPtr<rl4::MemoryResource> MemoryResource;` — Keep ref-count to shared memory resource alive in case the DNA asset is GCed during engine shutdown
- L172 _private member_ `TSharedPtr<IDNAReader> DNAReader;` — Unified DNA Reader used for run-time execution of RigLogic and updating of SkeletalMesh geometry
- L177 _private member_ `TSharedPtr<FSharedRigRuntimeContext> RigRuntimeContext;` — Runtime data necessary for rig computations that is shared between multiple rig instances based on the same DNA.
- L183 _private member_ `TMap<FSkeletalMeshSkeletonToDNAIndexMappingKey, TSharedPtr<FDNAIndexMapping>> DNAIndexMappingContainer;` — Container for Skeleton <-> DNAAsset index mappings The mapping object owners will be the SkeletalMeshes, and periodic cleanups will ensure that dead objects are deleted from the map.

#### struct `UDNA::FSkeletalMeshSkeletonToDNAIndexMappingKey`  
`struct FSkeletalMeshSkeletonToDNAIndexMappingKey`  
_L137-154_
- L139 _public member_ `TWeakObjectPtr<const USkeletalMesh> SkeletalMesh;`
- L140 _public member_ `TWeakObjectPtr<const USkeleton> Skeleton;`
- L142 _public function_ `bool operator==(const FSkeletalMeshSkeletonToDNAIndexMappingKey& Other) const`
- L146 _public function_ `bool operator!=(const FSkeletalMeshSkeletonToDNAIndexMappingKey& Other) const`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API RIGLOGICMODULE_API`
- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNA, Log, All);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNA, Log, All);`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/DNAAsset.h` (Public)


#### class `UDNAAsset`  
`class UDNAAsset : public UAssetUserData`  
_L41-186_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "Legacy MetaHuman DNA Data"))`
- inherits: `UAssetUserData`
- desc: An asset holding the data needed to generate/update/animate a RigLogic character It is imported from character's DNA file as a bit stream, and separated out it into runtime (behavior) and design-time chunks; Currently, the design-time part still loads the geometry, as it is needed for the skeletal mesh update; once SkeletalMeshDNAReader is fully implemented, it will be able to read the geometry directly from the SkeletalMesh and won't load it into this asset
- L46 _public prototype_ `UDNAAsset();`
- L47 _public prototype_ `~UDNAAsset();`
- L51 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = ImportSettings)`
- L55 _public prototype_ `TSharedPtr<IDNAReader> GetBehaviorReader();` — `UE_DEPRECATED(5.8, "This function has been deprecated, use GetDNAReader instead")`
- L59 _public prototype_ `TSharedPtr<IDNAReader> GetGeometryReader();` — `UE_DEPRECATED(5.8, "This function has been deprecated, use GetDNAReader instead")`
- L62 _public prototype_ `TSharedPtr<IDNAReader> GetDNAReader();`
- L65 _public member_ `FString DnaFileName_DEPRECATED;` — `UPROPERTY(AssetRegistrySearchable, meta = (DeprecatedProperty))`
- L74 _public member_ `bool bKeepDNAAfterInitialization;` — `UPROPERTY(EditAnywhere, Category = RuntimeSettings)` — In non-editor builds, the DNA source data will be unloaded to save memory after the runtime data has been initialized from it. Set this property to true to keep the DNA in memory, e.g. if you need to modify it at runtime. For most use cases, this shouldn't be needed.
- L80 _public member_ `TMap<FString, FString> MetaData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RuntimeSettings)` — Collection of runtime metadata related to a specific character. The value field is a FString and requires casting for a derived types.
- L83 _public member_ `FRigLogicConfiguration RigLogicConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RuntimeSettings)`
- L86 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L89 _public prototype_ `bool Init(const FString& Filename);`
- L90 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L99 _public prototype_ `void SetDNAReader(TSharedPtr<IDNAReader> SourceDNAReader, EDNACopyPolicy CopyPolicy = EDNACopyPolicy::Copy, ERigLogicInitPolicy InitPolicy = ERigLogicInitPolicy::Initialize);` — Used when importing behavior into archetype SkelMesh in the editor, and when updating SkeletalMesh runtime with GeneSplicer. Pass ERigLogicInitPolicy::Defer when this call is immediately followed by another operation that rebuilds the runtime context (e.g. RestoreLegacyUEMHCCompatibility) to avoid constructing an FRigLogic that will be thrown away.
- L104 _public prototype_ `void SetBehaviorReader(TSharedPtr<IDNAReader> SourceDNAReader);` — `UE_DEPRECATED(5.8, "This function has been deprecated, use SetDNAReader instead")`
- L106 _public prototype_ `void SetGeometryReader(TSharedPtr<IDNAReader> SourceDNAReader);` — `UE_DEPRECATED(5.8, "This function has been deprecated, use SetDNAReader instead")`
- L120 _public prototype_ `void InitializeForRuntimeFrom(UDNAAsset* Other);` — Initialize this object for use at runtime from another instance that has already been initialized. Overwrites all member variables. Only data needed for runtime evaluation will be copied. Performs a shallow copy, so the runtime data is shared between the two instances and the memory cost of the copied UDNAAsset is very low. Note that the reference to the shared runtime data will be dropped if the source DNA is modified, so the two instances are effectively independent and can safely be modified or deleted without affecting the other.
- L121 _public prototype_ `TSharedPtr<FSharedRigRuntimeContext> GetRigRuntimeContext();`
- L122 _public prototype_ `TSharedPtr<FDNAIndexMapping> GetDNAIndexMapping(const USkeleton* Skeleton, const USkeletalMesh* SkeletalMesh);`
- L125 _public prototype_ `const TSharedRef<IDNAReader> GetDnaReaderFromAsset();` — `UE_DEPRECATED(5.8, "This function has been deprecated, use GetDNAReader instead since now we don't need to pack in both Geometry and Behavior into one reader.")`
- L131 _public prototype_ `void RestoreLegacyUEMHCCompatibility();` — Fallback for users who have not updated to the new conversion workflow. Converts DNA reader data back to its original source space (Maya coordinate space) and provides RigLogic with the same transformed data as in the legacy pipeline.
- L137 _private prototype_ `void InvalidateRigRuntimeContext();`
- L138 _private prototype_ `void InitializeRigRuntimeContext(TSharedPtr<IDNAReader> ReaderForRigLogic);`
- L154 _private function_ `friend uint32 GetTypeHash(const FSkeletalMeshSkeletonToDNAIndexMappingKey& Instance)`
- L162 _private member_ `FTransactionallySafeRWLock DNAUpdateLock;` — Synchronize DNA updates
- L165 _private member_ `FTransactionallySafeRWLock RigRuntimeContextUpdateLock;` — Synchronize Rig Runtime Context updates
- L168 _private member_ `FTransactionallySafeRWLock DNAIndexMappingUpdateLock;` — Synchronize DNA Index Mapping updates
- L173 _private member_ `TSharedPtr<IDNAReader> DNAReader;` — Unified DNA Reader used for run-time execution of RigLogic and updating of SkeletalMesh geometry
- L178 _private member_ `TSharedPtr<FSharedRigRuntimeContext> RigRuntimeContext;` — Runtime data necessary for rig computations that is shared between multiple rig instances based on the same DNA.
- L184 _private member_ `TMap<FSkeletalMeshSkeletonToDNAIndexMappingKey, TSharedPtr<FDNAIndexMapping>> DNAIndexMappingContainer;` — Container for Skeleton <-> DNAAsset index mappings The mapping object owners will be the SkeletalMeshes, and periodic cleanups will ensure that dead objects are deleted from the map.

#### struct `UDNAAsset::FSkeletalMeshSkeletonToDNAIndexMappingKey`  
`struct FSkeletalMeshSkeletonToDNAIndexMappingKey`  
_L141-158_
- L143 _public member_ `TWeakObjectPtr<const USkeletalMesh> SkeletalMesh;`
- L144 _public member_ `TWeakObjectPtr<const USkeleton> Skeleton;`
- L146 _public function_ `bool operator==(const FSkeletalMeshSkeletonToDNAIndexMappingKey& Other) const`
- L150 _public function_ `bool operator!=(const FSkeletalMeshSkeletonToDNAIndexMappingKey& Other) const`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API RIGLOGICMODULE_API`
- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAAsset, Log, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAAsset, Log, All);`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/DNAAssetUserData.h` (Public)


#### class `UDNAAssetUserData`  
`class UDNAAssetUserData: public UAssetUserData`  
_L19-26_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "MetaHuman DNA Data"))`
- inherits: `UAssetUserData`
- L25 _public member_ `TObjectPtr<UDNA> DNAAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset", meta = (DisplayName = "DNA"))`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/DNACommon.h` (Public)


#### enum `EArchetype`  
`enum class EArchetype: uint8`  
_L14-22_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Asian`
- L17 _public enumerator_ `Black`
- L18 _public enumerator_ `Caucasian`
- L19 _public enumerator_ `Hispanic`
- L20 _public enumerator_ `Alien`
- L21 _public enumerator_ `Other`

#### enum `EGender`  
`enum class EGender: uint8`  
_L25-30_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `Male`
- L28 _public enumerator_ `Female`
- L29 _public enumerator_ `Other`

#### enum `ETranslationUnit`  
`enum class ETranslationUnit: uint8`  
_L33-37_
- reflection: `UENUM(BlueprintType)`
- L35 _public enumerator_ `CM`
- L36 _public enumerator_ `M`

#### enum `ERotationUnit`  
`enum class ERotationUnit: uint8`  
_L40-44_
- reflection: `UENUM(BlueprintType)`
- L42 _public enumerator_ `Degrees`
- L43 _public enumerator_ `Radians`

#### enum `EDirection`  
`enum class EDirection: uint8`  
_L47-55_
- reflection: `UENUM(BlueprintType)`
- L49 _public enumerator_ `Left`
- L50 _public enumerator_ `Right`
- L51 _public enumerator_ `Up`
- L52 _public enumerator_ `Down`
- L53 _public enumerator_ `Front`
- L54 _public enumerator_ `Back`

#### enum `ERotationSequence`  
`enum class ERotationSequence: uint8`  
_L58-66_
- reflection: `UENUM(BlueprintType)`
- L60 _public enumerator_ `XYZ`
- L61 _public enumerator_ `XZY`
- L62 _public enumerator_ `YXZ`
- L63 _public enumerator_ `YZX`
- L64 _public enumerator_ `ZXY`
- L65 _public enumerator_ `ZYX`

#### enum `ERotationDirection`  
`enum class ERotationDirection: uint8`  
_L69-73_
- reflection: `UENUM(BlueprintType)`
- L70 _public enumerator_ `None = 0 UMETA(Hidden)`
- L71 _public enumerator_ `Positive = 1`
- L72 _public enumerator_ `Negative = 255`

#### enum `EFaceWindingOrder`  
`enum class EFaceWindingOrder : uint8`  
_L79-83_
- reflection: `UENUM(BlueprintType)`
- desc: Face vertex winding order, viewed along the outward surface normal. CCW: cross product of consecutive face vertices points along the stored normal direction (Maya / OpenGL convention). CW:  cross product of consecutive face vertices opposes the stored normal direction (DirectX / UE renderer convention).
- L81 _public enumerator_ `CCW = 0`
- L82 _public enumerator_ `CW = 1`

#### enum `ETranslationRepresentation`  
`enum class ETranslationRepresentation : uint8`  
_L86-89_
- reflection: `UENUM(BlueprintType)`
- L88 _public enumerator_ `Vector`

#### enum `ERotationRepresentation`  
`enum class ERotationRepresentation : uint8`  
_L92-96_
- reflection: `UENUM(BlueprintType)`
- L94 _public enumerator_ `EulerAngles`
- L95 _public enumerator_ `Quaternion`

#### enum `EScaleRepresentation`  
`enum class EScaleRepresentation : uint8`  
_L99-102_
- reflection: `UENUM(BlueprintType)`
- L101 _public enumerator_ `Vector`

#### enum `EMachineLearnedBehaviorOperationType`  
`enum class EMachineLearnedBehaviorOperationType : uint8`  
_L105-112_
- reflection: `UENUM(BlueprintType)`
- L107 _public enumerator_ `Unspecified`
- L108 _public enumerator_ `Gather`
- L109 _public enumerator_ `Scatter`
- L110 _public enumerator_ `MLP`
- L111 _public enumerator_ `Average`

#### enum `EAutomaticRadius`  
`enum class EAutomaticRadius : uint8`  
_L150-154_
- reflection: `UENUM(BlueprintType)`
- L152 _public enumerator_ `On`
- L153 _public enumerator_ `Off`

#### enum `ETwistAxis`  
`enum class ETwistAxis : uint8`  
_L157-162_
- reflection: `UENUM(BlueprintType)`
- L159 _public enumerator_ `X`
- L160 _public enumerator_ `Y`
- L161 _public enumerator_ `Z`

#### enum `EDNADataLayer`  
`enum class EDNADataLayer : uint8`  
_L165-176_
- reflection: `UENUM(BlueprintType)`
- L167 _public enumerator_ `None`
- L168 _public enumerator_ `Descriptor = 1`
- L169 _public enumerator_ `Definition = 2 | Descriptor` — Implicitly loads Descriptor
- L170 _public enumerator_ `Behavior = 4 | Definition` — Implicitly loads Descriptor and Definition
- L171 _public enumerator_ `Geometry = 8 | Definition` — Implicitly loads Descriptor and Definition
- L172 _public enumerator_ `GeometryWithoutBlendShapes = 16 | Definition` — Implicitly loads Descriptor and Definition
- L173 _public enumerator_ `MachineLearnedBehavior = 32 | Definition` — Implicitly loads Definition
- L174 _public enumerator_ `RBFBehavior = 64 | Behavior` — Implicitly loads Behavior and all body-rig related layers
- L175 _public enumerator_ `All = RBFBehavior | Geometry | MachineLearnedBehavior`

#### enum `EDNADataLayerUIProxy`  
`enum class EDNADataLayerUIProxy : uint8`  
_L180-189_
- reflection: `UENUM(BlueprintType, meta = (Bitflags))`
- L182 _public enumerator_ `Descriptor = 0`
- L183 _public enumerator_ `Definition = 1`
- L184 _public enumerator_ `Behavior = 2`
- L185 _public enumerator_ `Geometry = 3`
- L186 _public enumerator_ `GeometryNoBlendShapes = 4`
- L187 _public enumerator_ `MLBehavior = 5`
- L188 _public enumerator_ `RBFBehavior = 6`

#### enum `ECoordinateSystemTransformPolicy`  
`enum class ECoordinateSystemTransformPolicy : uint8`  
_L192-195_
- reflection: `UENUM(BlueprintType)`
- L193 _public enumerator_ `Preserve`
- L194 _public enumerator_ `Transform`

#### enum `ERigLogicInitPolicy`  
`enum class ERigLogicInitPolicy : uint8`  
_L203-206_
- reflection: `UENUM(BlueprintType)`
- desc: Controls whether SetDNAReader rebuilds the RigLogic runtime context. Use Defer when SetDNAReader is immediately followed by another mutation (e.g. RestoreLegacyUEMHCCompatibility) that will rebuild the context anyway, to avoid the wasted FRigLogic construction.
- L204 _public enumerator_ `Initialize`
- L205 _public enumerator_ `Defer`

#### enum `EDNACopyPolicy`  
`enum class EDNACopyPolicy : uint8`  
_L221-224_
- reflection: `UENUM(BlueprintType)`
- desc: Controls whether SetDNAReader takes ownership of an independent copy of the source reader or aliases the input shared pointer directly. Copy (default): the asset performs a deep copy of the source reader. This isolates the asset from caller-side mutation. Alias: the asset stores the input TSharedPtr<IDNAReader> directly. Cheaper, but the asset's reader is then sensitive to caller-side mutation and retains all layers the source had. It is safe today because IDNAReader exposes only one non-const method (Unload), which is reachable only in non-editor builds. If a new mutator is added to IDNAReader, every Alias call site must be re-audited for cross-asset mutation hazards.
- L222 _public enumerator_ `Copy`
- L223 _public enumerator_ `Alias`

#### enum `EActivationFunction`  
`enum class EActivationFunction : uint8`  
_L227-234_
- reflection: `UENUM(BlueprintType)`
- L229 _public enumerator_ `Linear`
- L230 _public enumerator_ `ReLU`
- L231 _public enumerator_ `LeakyReLU`
- L232 _public enumerator_ `Tanh`
- L233 _public enumerator_ `Sigmoid`

#### struct `FRotationSign`  
`struct FRotationSign`  
_L237-265_
- reflection: `USTRUCT(BlueprintType)`
- L241 _public function_ `FRotationSign() : XAxis(), YAxis(), ZAxis()`
- L245 _public function_ `FRotationSign(ERotationDirection XAxis, ERotationDirection YAxis, ERotationDirection ZAxis) : XAxis(XAxis), YAxis(YAxis), ZAxis(ZAxis)`
- L249 _public function_ `bool operator==(const FRotationSign& Other) const`
- L254 _public function_ `bool operator!=(const FRotationSign& Other) const`
- L260 _public member_ `ERotationDirection XAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RigLogic")`
- L262 _public member_ `ERotationDirection YAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RigLogic")`
- L264 _public member_ `ERotationDirection ZAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RigLogic")`

#### struct `FCoordinateSystem`  
`struct FCoordinateSystem`  
_L268-296_
- reflection: `USTRUCT(BlueprintType)`
- L272 _public function_ `FCoordinateSystem() : XAxis(), YAxis(), ZAxis()`
- L276 _public function_ `FCoordinateSystem(EDirection XAxis, EDirection YAxis, EDirection ZAxis) : XAxis(XAxis), YAxis(YAxis), ZAxis(ZAxis)`
- L280 _public function_ `bool operator==(const FCoordinateSystem& Other) const`
- L285 _public function_ `bool operator!=(const FCoordinateSystem& Other) const`
- L291 _public member_ `EDirection XAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RigLogic")`
- L293 _public member_ `EDirection YAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RigLogic")`
- L295 _public member_ `EDirection ZAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RigLogic")`

#### struct `FDNAConfig`  
`struct FDNAConfig`  
_L299-370_
- reflection: `USTRUCT(BlueprintType)`
- L303 _public prototype_ `FDNAConfig() = default;`
- L305 _public function_ `FDNAConfig(EDNADataLayer Layers, FPerPlatformInt MaxLOD, FPerPlatformInt MinLOD, TArrayView<const uint16> ExactLODs, ECoordinateSystemTransformPolicy CoordinateSystemTransformPolicy, FCoordinateSystem CoordinateSystem, FRotationSign RotationSign, ERotationSequence RotationSequence) : Layers(static_cast<int32>(Layers)), MaxLODPerPlatform(MaxLOD), MinLODPerPlatform(MinLOD), ExactLODs(ExactLODs), CoordinateSystemTransformPolicy(CoordinateSystemTransformPolicy), CoordinateSystem(CoordinateSystem), RotationSign(RotationSign), RotationSequence(RotationSequence)`
- L317 _public function_ `static FDNAConfig Legacy(ECoordinateSystemTransformPolicy CoordinateSystemTransformPolicy = ECoordinateSystemTransformPolicy::Preserve)`
- L329 _public function_ `static FDNAConfig Source(ECoordinateSystemTransformPolicy CoordinateSystemTransformPolicy = ECoordinateSystemTransformPolicy::Preserve)`
- L342 _public member_ `int32 Layers = static_cast<int32>(EDNADataLayer::All);` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNA", meta = (Bitmask, BitmaskEnum = "/Script/RigLogicModule.EDNADataLayerUIProxy"))`
- L345 _public member_ `FPerPlatformInt MaxLODPerPlatform;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNA", meta = (DisplayName = "Max LOD"))`
- L348 _public member_ `FPerPlatformInt MinLODPerPlatform = {static_cast<int32>(-1)};` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNA", meta = (DisplayName = "Min LOD"))`
- L351 _public member_ `TArray<uint8> ExactLODs;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNA")`
- L354 _public member_ `mutable TArray<uint16> InternalExactLODs;` — `UPROPERTY(Transient)` — This is a hidden copy of the above blueprint-exposed exact LOD list so it can be safely converted to the lower level config
- L357 _public member_ `ECoordinateSystemTransformPolicy CoordinateSystemTransformPolicy = ECoordinateSystemTransformPolicy::Preserve;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNA")`
- L360 _public member_ `FCoordinateSystem CoordinateSystem = {EDirection::Left, EDirection::Front, EDirection::Up};` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNA")`
- L363 _public member_ `FRotationSign RotationSign = {ERotationDirection::Negative, ERotationDirection::Negative, ERotationDirection::Positive};` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNA")`
- L366 _public member_ `ERotationSequence RotationSequence = ERotationSequence::XYZ;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNA")`
- L369 _public member_ `EFaceWindingOrder FaceWindingOrder = EFaceWindingOrder::CW;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNA")`

#### class `UDNAConfigHolder`  
`class UDNAConfigHolder : public UObject`  
_L373-380_
- reflection: `UCLASS()`
- inherits: `UObject`
- L379 _public member_ `FDNAConfig Config;` — `UPROPERTY()`

#### struct `FMeshBlendShapeChannelMapping`  
`struct FMeshBlendShapeChannelMapping`  
_L383-399_
- reflection: `USTRUCT(BlueprintType)`
- L387 _public function_ `FMeshBlendShapeChannelMapping() : MeshIndex(), BlendShapeChannelIndex()`
- L391 _public function_ `FMeshBlendShapeChannelMapping(int32 MeshIndex, int32 BlendShapeChannelIndex) : MeshIndex(MeshIndex), BlendShapeChannelIndex(BlendShapeChannelIndex)`
- L396 _public member_ `int32 MeshIndex;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`
- L398 _public member_ `int32 BlendShapeChannelIndex;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`

#### struct `FTextureCoordinate`  
`struct FTextureCoordinate`  
_L402-418_
- reflection: `USTRUCT(BlueprintType)`
- L406 _public function_ `FTextureCoordinate() : U(), V()`
- L410 _public function_ `FTextureCoordinate(float U, float V) : U(U), V(V)`
- L415 _public member_ `float U;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`
- L417 _public member_ `float V;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`

#### struct `FVertexLayout`  
`struct FVertexLayout`  
_L421-439_
- reflection: `USTRUCT(BlueprintType)`
- L425 _public function_ `FVertexLayout() : Position(), TextureCoordinate(), Normal()`
- L429 _public function_ `FVertexLayout(int32 Position, int32 TextureCoordinate, int32 Normal) : Position(Position), TextureCoordinate(TextureCoordinate), Normal(Normal)`
- L434 _public member_ `int32 Position;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`
- L436 _public member_ `int32 TextureCoordinate;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`
- L438 _public member_ `int32 Normal;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`

#### Free symbols / members of external scopes

- L177 _prototype_ `ENUM_CLASS_FLAGS(EDNADataLayer);`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/DNAIndexMapping.h` (Public)


#### struct `FDNAIndexMapping`  
`struct FDNAIndexMapping`  
_L16-55_
- L34 _public typedef_ `using FCachedIndexedCurve = TBaseBlendedCurve<FDefaultAllocator, UE::Anim::FCurveElementIndexed>;`
- L36 _public member_ `FGuid SkeletonGuid;`
- L39 _public member_ `FCachedIndexedCurve ControlAttributeCurves;` — all the control attributes that we will need to extract, alongside their control index
- L40 _public member_ `FCachedIndexedCurve MLMaskCurves;`
- L41 _public member_ `TArray<FMeshPoseBoneControlAttributeMapping> DriverJointsToControlAttributesMap;`
- L42 _public member_ `TArray<FMeshPoseBoneIndex> JointsMapDNAIndicesToMeshPoseBoneIndices;`
- L43 _public member_ `TArray<FCachedIndexedCurve> MorphTargetCurvesPerLOD;`
- L44 _public member_ `TArray<FCachedIndexedCurve> MaskMultiplierCurvesPerLOD;`
- L46 _public prototype_ `void Init(const IDNAReader* DNAReader, const USkeleton* Skeleton, const USkeletalMesh* SkeletalMesh);`
- L48 _public prototype_ `void MapControlCurves(const IDNAReader* DNAReader, const USkeleton* Skeleton);`
- L49 _public prototype_ `void MapMLMaskCurves(const IDNAReader* DNAReader, const USkeleton* Skeleton);`
- L50 _public prototype_ `void MapDriverJoints(const IDNAReader* DNAReader, const USkeletalMesh* SkeletalMesh);`
- L51 _public prototype_ `void MapJoints(const IDNAReader* DNAReader, const USkeletalMesh* SkeletalMesh);`
- L52 _public prototype_ `void MapMorphTargets(const IDNAReader* DNAReader, const USkeleton* Skeleton, const USkeletalMesh* SkeletalMesh);`
- L53 _public prototype_ `void MapMaskMultipliers(const IDNAReader* DNAReader, const USkeleton* Skeleton);`

#### struct `FDNAIndexMapping::TArrayWrapper`  
`template <typename T> struct TArrayWrapper`  
_L19-22_
- L21 _public member_ `TArray<T> Values;`

#### struct `FDNAIndexMapping::FMeshPoseBoneControlAttributeMapping`  
`struct FMeshPoseBoneControlAttributeMapping`  
_L24-32_
- L26 _public member_ `FMeshPoseBoneIndex MeshPoseBoneIndex;`
- L27 _public member_ `int32 DNAJointIndex;`
- L28 _public member_ `int32 RotationX;`
- L29 _public member_ `int32 RotationY;`
- L30 _public member_ `int32 RotationZ;`
- L31 _public member_ `int32 RotationW;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGLOGICMODULE_API`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/DNAReader.h` (Public)


#### class `IDNAReaderBase`  
`class IDNAReaderBase`  
_L22-46_
- L25 _protected prototype_ `virtual ~IDNAReaderBase() = default;`
- L28 _public prototype_ `virtual dna::Reader* Unwrap() const = 0;`
- L29 _public prototype_ `virtual void Unload(EDNADataLayer Layer) = 0;`
- L37 _public prototype_ `virtual const FDNAConfig& GetConfig() const = 0;` — Returns the FDNAConfig the reader was constructed with, with all per-platform fields resolved to scalar values for the host platform that built it. Use this to compare host config against a cook-target config without going through TPerPlatformProperty::GetValue() (which reads OnGetPreviewPlatform, an FNotThreadSafeDelegate that the cook server may rebind concurrently).
- L44 _public function_ `virtual bool IsLegacyWrapped() const` — Returns true if this reader is wrapped in the legacy adapter (FLegacyDNAReader), which applies the legacy Maya->UE coordinate swizzle on geometry queries regardless of FDNAConfig. Used by callers that must preserve UEMHC backwards-compatible behavior (e.g. RestoreLegacyUEMHCCompatibility) to detect when re-wrapping is required.

#### class `IHeaderReader`  
`class IHeaderReader : public IDNAReaderBase`  
_L48-57_
- inherits: `IDNAReaderBase`
- L51 _protected prototype_ `virtual ~IHeaderReader() = default;`
- L54 _public prototype_ `virtual uint16 GetFileFormatGeneration() const = 0;`
- L55 _public prototype_ `virtual uint16 GetFileFormatVersion() const = 0;`

#### class `IDescriptorReader`  
`class IDescriptorReader : public IHeaderReader`  
_L59-83_
- inherits: `IHeaderReader`
- L62 _protected prototype_ `virtual ~IDescriptorReader() = default;`
- L65 _public prototype_ `virtual FString GetName() const = 0;`
- L66 _public prototype_ `virtual EArchetype GetArchetype() const = 0;`
- L67 _public prototype_ `virtual EGender GetGender() const = 0;`
- L68 _public prototype_ `virtual uint16 GetAge() const = 0;`
- L69 _public prototype_ `virtual uint32 GetMetaDataCount() const = 0;`
- L70 _public prototype_ `virtual FString GetMetaDataKey(uint32 Index) const = 0;`
- L71 _public prototype_ `virtual FString GetMetaDataValue(const FString& Key) const = 0;`
- L72 _public prototype_ `virtual ETranslationUnit GetTranslationUnit() const = 0;`
- L73 _public prototype_ `virtual ERotationUnit GetRotationUnit() const = 0;`
- L74 _public prototype_ `virtual FCoordinateSystem GetCoordinateSystem() const = 0;`
- L75 _public prototype_ `virtual ERotationSequence GetRotationSequence() const = 0;`
- L76 _public prototype_ `virtual FRotationSign GetRotationSign() const = 0;`
- L77 _public prototype_ `virtual EFaceWindingOrder GetFaceWindingOrder() const = 0;`
- L78 _public prototype_ `virtual uint16 GetLODCount() const = 0;`
- L79 _public prototype_ `virtual uint16 GetDBMaxLOD() const = 0;`
- L80 _public prototype_ `virtual FString GetDBComplexity() const = 0;`
- L81 _public prototype_ `virtual FString GetDBName() const = 0;`

#### class `IDefinitionReader`  
`class IDefinitionReader : public IDescriptorReader`  
_L85-117_
- inherits: `IDescriptorReader`
- L88 _protected prototype_ `virtual ~IDefinitionReader() = default;`
- L91 _public prototype_ `virtual uint16 GetGUIControlCount() const = 0;`
- L92 _public prototype_ `virtual FString GetGUIControlName(uint16 Index) const = 0;`
- L93 _public prototype_ `virtual uint16 GetRawControlCount() const = 0;`
- L94 _public prototype_ `virtual FString GetRawControlName(uint16 Index) const = 0;`
- L95 _public prototype_ `virtual uint16 GetJointCount() const = 0;`
- L96 _public prototype_ `virtual FString GetJointName(uint16 Index) const = 0;`
- L97 _public prototype_ `virtual uint16 GetJointIndexListCount() const = 0;`
- L98 _public prototype_ `virtual TArrayView<const uint16> GetJointIndicesForLOD(uint16 LOD) const = 0;`
- L99 _public prototype_ `virtual uint16 GetJointParentIndex(uint16 Index) const = 0;`
- L100 _public prototype_ `virtual uint16 GetBlendShapeChannelCount() const = 0;`
- L101 _public prototype_ `virtual FString GetBlendShapeChannelName(uint16 Index) const = 0;`
- L102 _public prototype_ `virtual uint16 GetBlendShapeChannelIndexListCount() const = 0;`
- L103 _public prototype_ `virtual TArrayView<const uint16> GetBlendShapeChannelIndicesForLOD(uint16 LOD) const = 0;`
- L104 _public prototype_ `virtual uint16 GetAnimatedMapCount() const = 0;`
- L105 _public prototype_ `virtual FString GetAnimatedMapName(uint16 Index) const = 0;`
- L106 _public prototype_ `virtual uint16 GetAnimatedMapIndexListCount() const = 0;`
- L107 _public prototype_ `virtual TArrayView<const uint16> GetAnimatedMapIndicesForLOD(uint16 LOD) const = 0;`
- L108 _public prototype_ `virtual uint16 GetMeshCount() const = 0;`
- L109 _public prototype_ `virtual FString GetMeshName(uint16 Index) const = 0;`
- L110 _public prototype_ `virtual uint16 GetMeshIndexListCount() const = 0;`
- L111 _public prototype_ `virtual TArrayView<const uint16> GetMeshIndicesForLOD(uint16 LOD) const = 0;`
- L112 _public prototype_ `virtual uint16 GetMeshBlendShapeChannelMappingCount() const = 0;`
- L113 _public prototype_ `virtual FMeshBlendShapeChannelMapping GetMeshBlendShapeChannelMapping(uint16 Index) const = 0;`
- L114 _public prototype_ `virtual TArrayView<const uint16> GetMeshBlendShapeChannelMappingIndicesForLOD(uint16 LOD) const = 0;`
- L115 _public prototype_ `virtual FVector GetNeutralJointTranslation(uint16 Index) const = 0;`
- L116 _public prototype_ `virtual FVector GetNeutralJointRotation(uint16 Index) const = 0;`

#### class `IBehaviorReader`  
`class IBehaviorReader : public virtual IDefinitionReader`  
_L119-154_
- inherits: `IDefinitionReader`
- L122 _protected prototype_ `virtual ~IBehaviorReader() = default;`
- L125 _public prototype_ `virtual TArrayView<const uint16> GetGUIToRawInputIndices() const = 0;`
- L126 _public prototype_ `virtual TArrayView<const uint16> GetGUIToRawOutputIndices() const = 0;`
- L127 _public prototype_ `virtual TArrayView<const float> GetGUIToRawFromValues() const = 0;`
- L128 _public prototype_ `virtual TArrayView<const float> GetGUIToRawToValues() const = 0;`
- L129 _public prototype_ `virtual TArrayView<const float> GetGUIToRawSlopeValues() const = 0;`
- L130 _public prototype_ `virtual TArrayView<const float> GetGUIToRawCutValues() const = 0;`
- L131 _public prototype_ `virtual uint16 GetPSDCount() const = 0;`
- L132 _public prototype_ `virtual TArrayView<const uint16> GetPSDRowIndices() const = 0;`
- L133 _public prototype_ `virtual TArrayView<const uint16> GetPSDColumnIndices() const = 0;`
- L134 _public prototype_ `virtual TArrayView<const float> GetPSDValues() const = 0;`
- L135 _public prototype_ `virtual uint16 GetJointRowCount() const = 0;`
- L136 _public prototype_ `virtual uint16 GetJointColumnCount() const = 0;`
- L137 _public prototype_ `virtual TArrayView<const uint16> GetJointVariableAttributeIndices(uint16 LOD) const = 0;`
- L138 _public prototype_ `virtual uint16 GetJointGroupCount() const = 0;`
- L139 _public prototype_ `virtual TArrayView<const uint16> GetJointGroupLODs(uint16 JointGroupIndex) const = 0;`
- L140 _public prototype_ `virtual TArrayView<const uint16> GetJointGroupInputIndices(uint16 JointGroupIndex) const = 0;`
- L141 _public prototype_ `virtual TArrayView<const uint16> GetJointGroupOutputIndices(uint16 JointGroupIndex) const = 0;`
- L142 _public prototype_ `virtual TArrayView<const float> GetJointGroupValues(uint16 JointGroupIndex) const = 0;`
- L143 _public prototype_ `virtual TArrayView<const uint16> GetJointGroupJointIndices(uint16 JointGroupIndex) const = 0;`
- L144 _public prototype_ `virtual TArrayView<const uint16> GetBlendShapeChannelLODs() const = 0;`
- L145 _public prototype_ `virtual TArrayView<const uint16> GetBlendShapeChannelOutputIndices() const = 0;`
- L146 _public prototype_ `virtual TArrayView<const uint16> GetBlendShapeChannelInputIndices() const = 0;`
- L147 _public prototype_ `virtual TArrayView<const uint16> GetAnimatedMapLODs() const = 0;`
- L148 _public prototype_ `virtual TArrayView<const uint16> GetAnimatedMapInputIndices() const = 0;`
- L149 _public prototype_ `virtual TArrayView<const uint16> GetAnimatedMapOutputIndices() const = 0;`
- L150 _public prototype_ `virtual TArrayView<const float> GetAnimatedMapFromValues() const = 0;`
- L151 _public prototype_ `virtual TArrayView<const float> GetAnimatedMapToValues() const = 0;`
- L152 _public prototype_ `virtual TArrayView<const float> GetAnimatedMapSlopeValues() const = 0;`
- L153 _public prototype_ `virtual TArrayView<const float> GetAnimatedMapCutValues() const = 0;`

#### class `IGeometryReader`  
`class IGeometryReader : public virtual IDefinitionReader`  
_L156-187_
- inherits: `IDefinitionReader`
- L159 _protected prototype_ `virtual ~IGeometryReader() = default;`
- L162 _public prototype_ `virtual uint32 GetVertexPositionCount(uint16 MeshIndex) const = 0;`
- L163 _public prototype_ `virtual FVector GetVertexPosition(uint16 MeshIndex, uint32 VertexIndex) const = 0;`
- L164 _public prototype_ `virtual TArrayView<const float> GetVertexPositionXs(uint16 MeshIndex) const = 0;`
- L165 _public prototype_ `virtual TArrayView<const float> GetVertexPositionYs(uint16 MeshIndex) const = 0;`
- L166 _public prototype_ `virtual TArrayView<const float> GetVertexPositionZs(uint16 MeshIndex) const = 0;`
- L167 _public prototype_ `virtual uint32 GetVertexTextureCoordinateCount(uint16 MeshIndex) const = 0;`
- L168 _public prototype_ `virtual FTextureCoordinate GetVertexTextureCoordinate(uint16 MeshIndex, uint32 TextureCoordinateIndex) const = 0;`
- L169 _public prototype_ `virtual uint32 GetVertexNormalCount(uint16 MeshIndex) const = 0;`
- L170 _public prototype_ `virtual FVector GetVertexNormal(uint16 MeshIndex, uint32 NormalIndex) const = 0;`
- L171 _public prototype_ `virtual uint32 GetFaceCount(uint16 MeshIndex) const = 0;`
- L172 _public prototype_ `virtual TArrayView<const uint32> GetFaceVertexLayoutIndices(uint16 MeshIndex, uint32 FaceIndex) const = 0;`
- L173 _public prototype_ `virtual uint32 GetVertexLayoutCount(uint16 MeshIndex) const = 0;`
- L174 _public prototype_ `virtual FVertexLayout GetVertexLayout(uint16 MeshIndex, uint32 LayoutIndex) const = 0;`
- L175 _public prototype_ `virtual uint16 GetMaximumInfluencePerVertex(uint16 MeshIndex) const = 0;`
- L176 _public prototype_ `virtual uint32 GetSkinWeightsCount(uint16 MeshIndex) const = 0;`
- L177 _public prototype_ `virtual TArrayView<const float> GetSkinWeightsValues(uint16 MeshIndex, uint32 VertexIndex) const = 0;`
- L178 _public prototype_ `virtual TArrayView<const uint16> GetSkinWeightsJointIndices(uint16 MeshIndex, uint32 VertexIndex) const = 0;`
- L179 _public prototype_ `virtual uint16 GetBlendShapeTargetCount(uint16 MeshIndex) const = 0;`
- L180 _public prototype_ `virtual uint16 GetBlendShapeChannelIndex(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const = 0;`
- L181 _public prototype_ `virtual uint32 GetBlendShapeTargetDeltaCount(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const = 0;`
- L182 _public prototype_ `virtual FVector GetBlendShapeTargetDelta(uint16 MeshIndex, uint16 BlendShapeTargetIndex, uint32 DeltaIndex) const = 0;`
- L183 _public prototype_ `virtual TArrayView<const float> GetBlendShapeTargetDeltaXs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const = 0;`
- L184 _public prototype_ `virtual TArrayView<const float> GetBlendShapeTargetDeltaYs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const = 0;`
- L185 _public prototype_ `virtual TArrayView<const float> GetBlendShapeTargetDeltaZs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const = 0;`
- L186 _public prototype_ `virtual TArrayView<const uint32> GetBlendShapeTargetVertexIndices(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const = 0;`

#### class `IMachineLearnedBehaviorReader`  
`class IMachineLearnedBehaviorReader : public virtual IDefinitionReader`  
_L189-211_
- inherits: `IDefinitionReader`
- L192 _protected prototype_ `virtual ~IMachineLearnedBehaviorReader() = default;`
- L195 _public prototype_ `virtual uint16 GetMLControlCount() const = 0;`
- L196 _public prototype_ `virtual FString GetMLControlName(uint16 Index) const = 0;`
- L197 _public prototype_ `virtual uint16 GetNeuralNetworkCount() const = 0;`
- L198 _public prototype_ `virtual uint16 GetNeuralNetworkIndexListCount() const = 0;`
- L199 _public prototype_ `virtual TArrayView<const uint16> GetNeuralNetworkIndicesForLOD(uint16 LOD) const = 0;`
- L200 _public prototype_ `virtual uint16 GetMeshRegionCount(uint16 MeshIndex) const = 0;`
- L201 _public prototype_ `virtual FString GetMeshRegionName(uint16 MeshIndex, uint16 RegionIndex) const = 0;`
- L202 _public prototype_ `virtual TArrayView<const uint16> GetNeuralNetworkIndicesForMeshRegion(uint16 MeshIndex, uint16 RegionIndex) const = 0;`
- L203 _public prototype_ `virtual TArrayView<const uint16> GetNeuralNetworkInputIndices(uint16 NetIndex) const = 0;`
- L204 _public prototype_ `virtual TArrayView<const uint16> GetNeuralNetworkOutputIndices(uint16 NetIndex) const = 0;`
- L205 _public prototype_ `virtual uint16 GetNeuralNetworkLayerCount(uint16 NetIndex) const = 0;`
- L206 _public prototype_ `virtual EActivationFunction GetNeuralNetworkLayerActivationFunction(uint16 NetIndex, uint16 LayerIndex) const = 0;`
- L207 _public prototype_ `virtual TArrayView<const float> GetNeuralNetworkLayerActivationFunctionParameters(uint16 NetIndex, uint16 LayerIndex) const = 0;`
- L208 _public prototype_ `virtual TArrayView<const float> GetNeuralNetworkLayerBiases(uint16 NetIndex, uint16 LayerIndex) const = 0;`
- L209 _public prototype_ `virtual TArrayView<const float> GetNeuralNetworkLayerWeights(uint16 NetIndex, uint16 LayerIndex) const = 0;`

#### class `IJointBehaviorMetadataReader`  
`class IJointBehaviorMetadataReader : public virtual IDefinitionReader`  
_L213-223_
- inherits: `IDefinitionReader`
- L216 _protected prototype_ `virtual ~IJointBehaviorMetadataReader() = default;`
- L219 _public prototype_ `virtual ETranslationRepresentation GetJointTranslationRepresentation(uint16 JointIndex) const = 0;`
- L220 _public prototype_ `virtual ERotationRepresentation GetJointRotationRepresentation(uint16 JointIndex) const = 0;`
- L221 _public prototype_ `virtual EScaleRepresentation GetJointScaleRepresentation(uint16 JointIndex) const = 0;`

#### class `IRBFBehaviorReader`  
`class IRBFBehaviorReader : public virtual IBehaviorReader`  
_L225-259_
- inherits: `IBehaviorReader`
- L228 _protected prototype_ `virtual ~IRBFBehaviorReader() = default;`
- L231 _public prototype_ `virtual uint16 GetRBFPoseCount() const = 0;`
- L232 _public prototype_ `virtual FString GetRBFPoseName(uint16 PoseIndex) const = 0;`
- L233 _public prototype_ `virtual TArrayView<const uint16> GetRBFPoseJointOutputIndices(uint16 PoseIndex) const = 0;`
- L234 _public prototype_ `virtual TArrayView<const uint16> GetRBFPoseBlendShapeChannelOutputIndices(uint16 PoseIndex) const = 0;`
- L235 _public prototype_ `virtual TArrayView<const uint16> GetRBFPoseAnimatedMapOutputIndices(uint16 PoseIndex) const = 0;`
- L236 _public prototype_ `virtual TArrayView<const float> GetRBFPoseJointOutputValues(uint16 PoseIndex) const = 0;`
- L237 _public prototype_ `virtual float GetRBFPoseScale(uint16 PoseIndex) const = 0;`
- L238 _public prototype_ `virtual uint16 GetRBFPoseControlCount() const = 0;`
- L239 _public prototype_ `virtual FString GetRBFPoseControlName(uint16 PoseControlIndex) const = 0;`
- L240 _public prototype_ `virtual TArrayView<const uint16> GetRBFPoseInputControlIndices(uint16 PoseIndex) const = 0;`
- L241 _public prototype_ `virtual TArrayView<const uint16> GetRBFPoseOutputControlIndices(uint16 PoseIndex) const = 0;`
- L242 _public prototype_ `virtual TArrayView<const float> GetRBFPoseOutputControlWeights(uint16 PoseIndex) const = 0;`
- L243 _public prototype_ `virtual uint16 GetRBFSolverCount() const = 0;`
- L244 _public prototype_ `virtual uint16 GetRBFSolverIndexListCount() const = 0;`
- L245 _public prototype_ `virtual TArrayView<const uint16> GetRBFSolverIndicesForLOD(uint16 LOD) const = 0;`
- L246 _public prototype_ `virtual FString GetRBFSolverName(uint16 SolverIndex) const = 0;`
- L247 _public prototype_ `virtual TArrayView<const uint16> GetRBFSolverRawControlIndices(uint16 SolverIndex) const = 0;`
- L248 _public prototype_ `virtual TArrayView<const uint16> GetRBFSolverPoseIndices(uint16 SolverIndex) const = 0;`
- L249 _public prototype_ `virtual TArrayView<const float> GetRBFSolverRawControlValues(uint16 SolverIndex) const = 0;`
- L250 _public prototype_ `virtual ERBFSolverType GetRBFSolverType(uint16 SolverIndex) const = 0;`
- L251 _public prototype_ `virtual float GetRBFSolverRadius(uint16 SolverIndex) const = 0;`
- L252 _public prototype_ `virtual EAutomaticRadius GetRBFSolverAutomaticRadius(uint16 SolverIndex) const = 0;`
- L253 _public prototype_ `virtual float GetRBFSolverWeightThreshold(uint16 SolverIndex) const = 0;`
- L254 _public prototype_ `virtual ERBFDistanceMethod GetRBFSolverDistanceMethod(uint16 SolverIndex) const = 0;`
- L255 _public prototype_ `virtual ERBFNormalizeMethod GetRBFSolverNormalizeMethod(uint16 SolverIndex) const = 0;`
- L256 _public prototype_ `virtual ERBFFunctionType GetRBFSolverFunctionType(uint16 SolverIndex) const = 0;`
- L257 _public prototype_ `virtual ETwistAxis GetRBFSolverTwistAxis(uint16 SolverIndex) const = 0;`

#### class `ITwistSwingBehaviorReader`  
`class ITwistSwingBehaviorReader : public virtual IDefinitionReader`  
_L261-278_
- inherits: `IDefinitionReader`
- L264 _protected prototype_ `virtual ~ITwistSwingBehaviorReader() = default;`
- L267 _public prototype_ `virtual uint16 GetTwistCount() const = 0;`
- L268 _public prototype_ `virtual ETwistAxis GetTwistSetupTwistAxis(uint16 TwistIndex) const = 0;`
- L269 _public prototype_ `virtual TArrayView<const uint16> GetTwistInputControlIndices(uint16 TwistIndex) const = 0;`
- L270 _public prototype_ `virtual TArrayView<const uint16> GetTwistOutputJointIndices(uint16 TwistIndex) const = 0;`
- L271 _public prototype_ `virtual TArrayView<const float> GetTwistBlendWeights(uint16 TwistIndex) const = 0;`
- L272 _public prototype_ `virtual uint16 GetSwingCount() const = 0;`
- L273 _public prototype_ `virtual ETwistAxis GetSwingSetupTwistAxis(uint16 SwingIndex) const = 0;`
- L274 _public prototype_ `virtual TArrayView<const uint16> GetSwingInputControlIndices(uint16 SwingIndex) const = 0;`
- L275 _public prototype_ `virtual TArrayView<const uint16> GetSwingOutputJointIndices(uint16 SwingIndex) const = 0;`
- L276 _public prototype_ `virtual TArrayView<const float> GetSwingBlendWeights(uint16 SwingIndex) const = 0;`

#### class `IMachineLearnedBehaviorExtReader`  
`class IMachineLearnedBehaviorExtReader : public virtual IMachineLearnedBehaviorReader`  
_L280-300_
- inherits: `IMachineLearnedBehaviorReader`
- L283 _protected prototype_ `virtual ~IMachineLearnedBehaviorExtReader() = default;`
- L286 _public prototype_ `virtual uint16 GetMLTypeCount() const = 0;`
- L287 _public prototype_ `virtual uint16 GetMLOperationSetCount(uint16 MLTypeIndex) const = 0;`
- L288 _public prototype_ `virtual uint16 GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const = 0;`
- L289 _public prototype_ `virtual EMachineLearnedBehaviorOperationType GetMLOperationType(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const = 0;`
- L290 _public prototype_ `virtual TArrayView<const uint32> GetMLOperationParameters(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const = 0;`
- L291 _public prototype_ `virtual TArrayView<const uint16> GetMLOperationDependencyOperationSetIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const = 0;`
- L292 _public prototype_ `virtual TArrayView<const uint16> GetMLOperationDependencyOperationIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const = 0;`
- L293 _public prototype_ `virtual uint16 GetMLOperationIndexListCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const = 0;`
- L294 _public prototype_ `virtual TArrayView<const uint16> GetMLOperationIndicesForLOD(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 LOD) const = 0;`
- L295 _public prototype_ `virtual TArrayView<const uint16> GetMLJointsInputIndices() const = 0;`
- L296 _public prototype_ `virtual TArrayView<const uint16> GetMLJointsOutputIndices() const = 0;`
- L297 _public prototype_ `virtual TArrayView<const uint16> GetMLJointsParameterKeys() const = 0;`
- L298 _public prototype_ `virtual TArrayView<const uint16> GetMLJointsParameterValues() const = 0;`

#### class `IDNAReader`  
`class IDNAReader : public IRBFBehaviorReader, public IGeometryReader, public IMachineLearnedBehaviorExtReader, public IJointBehaviorMetadataReader, public ITwistSwingBehaviorReader`  
_L305-309_
- inherits: `IRBFBehaviorReader,IGeometryReader,IMachineLearnedBehaviorExtReader,IJointBehaviorMetadataReader,ITwistSwingBehaviorReader`
- desc: @brief UE interface for DNA Reader wrappers.
- L308 _public prototype_ `virtual ~IDNAReader() = default;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAReader, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAReader, Log, All);`
- L15 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/DNAReaderAdapter.h` (Public)


#### class `FDNAReader`  
`template <class TWrappedReader> class FDNAReader : public IDNAReader`  
_L12-218_
- inherits: `IDNAReader`
- L15 _public prototype_ `FDNAReader(TWrappedReader* Source, const FDNAConfig& InConfig);`
- L16 _public prototype_ `~FDNAReader() = default;`
- L18 _public prototype_ `FDNAReader(const FDNAReader&) = delete;`
- L19 _public prototype_ `FDNAReader& operator=(const FDNAReader&) = delete;`
- L21 _public prototype_ `FDNAReader(FDNAReader&&) = default;`
- L22 _public prototype_ `FDNAReader& operator=(FDNAReader&&) = default;`
- L25 _public prototype_ `uint16 GetFileFormatGeneration() const override;` — Header
- L26 _public prototype_ `uint16 GetFileFormatVersion() const override;`
- L28 _public prototype_ `FString GetName() const override;` — Descriptor
- L29 _public prototype_ `EArchetype GetArchetype() const override;`
- L30 _public prototype_ `EGender GetGender() const override;`
- L31 _public prototype_ `uint16 GetAge() const override;`
- L32 _public prototype_ `uint32 GetMetaDataCount() const override;`
- L33 _public prototype_ `FString GetMetaDataKey(uint32 Index) const override;`
- L34 _public prototype_ `FString GetMetaDataValue(const FString& Key) const override;`
- L35 _public prototype_ `ETranslationUnit GetTranslationUnit() const override;`
- L36 _public prototype_ `ERotationUnit GetRotationUnit() const override;`
- L37 _public prototype_ `FCoordinateSystem GetCoordinateSystem() const override;`
- L38 _public prototype_ `ERotationSequence GetRotationSequence() const override;`
- L39 _public prototype_ `FRotationSign GetRotationSign() const override;`
- L40 _public prototype_ `EFaceWindingOrder GetFaceWindingOrder() const override;`
- L41 _public prototype_ `uint16 GetLODCount() const override;`
- L42 _public prototype_ `uint16 GetDBMaxLOD() const override;`
- L43 _public prototype_ `FString GetDBComplexity() const override;`
- L44 _public prototype_ `FString GetDBName() const override;`
- L46 _public prototype_ `uint16 GetGUIControlCount() const override;` — Definition
- L47 _public prototype_ `FString GetGUIControlName(uint16 Index) const override;`
- L48 _public prototype_ `uint16 GetRawControlCount() const override;`
- L49 _public prototype_ `FString GetRawControlName(uint16 Index) const override;`
- L50 _public prototype_ `uint16 GetJointCount() const override;`
- L51 _public prototype_ `FString GetJointName(uint16 Index) const override;`
- L52 _public prototype_ `uint16 GetJointIndexListCount() const override;`
- L53 _public prototype_ `TArrayView<const uint16> GetJointIndicesForLOD(uint16 LOD) const override;`
- L54 _public prototype_ `uint16 GetJointParentIndex(uint16 Index) const override;`
- L55 _public prototype_ `uint16 GetBlendShapeChannelCount() const override;`
- L56 _public prototype_ `FString GetBlendShapeChannelName(uint16 Index) const override;`
- L57 _public prototype_ `uint16 GetBlendShapeChannelIndexListCount() const override;`
- L58 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelIndicesForLOD(uint16 LOD) const override;`
- L59 _public prototype_ `uint16 GetAnimatedMapCount() const override;`
- L60 _public prototype_ `FString GetAnimatedMapName(uint16 Index) const override;`
- L61 _public prototype_ `uint16 GetAnimatedMapIndexListCount() const override;`
- L62 _public prototype_ `TArrayView<const uint16> GetAnimatedMapIndicesForLOD(uint16 LOD) const override;`
- L63 _public prototype_ `uint16 GetMeshCount() const override;`
- L64 _public prototype_ `FString GetMeshName(uint16 Index) const override;`
- L65 _public prototype_ `uint16 GetMeshIndexListCount() const override;`
- L66 _public prototype_ `TArrayView<const uint16> GetMeshIndicesForLOD(uint16 LOD) const override;`
- L67 _public prototype_ `uint16 GetMeshBlendShapeChannelMappingCount() const override;`
- L68 _public prototype_ `FMeshBlendShapeChannelMapping GetMeshBlendShapeChannelMapping(uint16 Index) const override;`
- L69 _public prototype_ `TArrayView<const uint16> GetMeshBlendShapeChannelMappingIndicesForLOD(uint16 LOD) const override;`
- L70 _public prototype_ `FVector GetNeutralJointTranslation(uint16 Index) const override;`
- L71 _public prototype_ `FVector GetNeutralJointRotation(uint16 Index) const override;`
- L73 _public prototype_ `TArrayView<const uint16> GetGUIToRawInputIndices() const override;` — Behavior
- L74 _public prototype_ `TArrayView<const uint16> GetGUIToRawOutputIndices() const override;`
- L75 _public prototype_ `TArrayView<const float> GetGUIToRawFromValues() const override;`
- L76 _public prototype_ `TArrayView<const float> GetGUIToRawToValues() const override;`
- L77 _public prototype_ `TArrayView<const float> GetGUIToRawSlopeValues() const override;`
- L78 _public prototype_ `TArrayView<const float> GetGUIToRawCutValues() const override;`
- L79 _public prototype_ `uint16 GetPSDCount() const override;`
- L80 _public prototype_ `TArrayView<const uint16> GetPSDRowIndices() const override;`
- L81 _public prototype_ `TArrayView<const uint16> GetPSDColumnIndices() const override;`
- L82 _public prototype_ `TArrayView<const float> GetPSDValues() const override;`
- L83 _public prototype_ `uint16 GetJointRowCount() const override;`
- L84 _public prototype_ `uint16 GetJointColumnCount() const override;`
- L85 _public prototype_ `TArrayView<const uint16> GetJointVariableAttributeIndices(uint16 LOD) const override;`
- L86 _public prototype_ `uint16 GetJointGroupCount() const override;`
- L87 _public prototype_ `TArrayView<const uint16> GetJointGroupLODs(uint16 JointGroupIndex) const override;`
- L88 _public prototype_ `TArrayView<const uint16> GetJointGroupInputIndices(uint16 JointGroupIndex) const override;`
- L89 _public prototype_ `TArrayView<const uint16> GetJointGroupOutputIndices(uint16 JointGroupIndex) const override;`
- L90 _public prototype_ `TArrayView<const float> GetJointGroupValues(uint16 JointGroupIndex) const override;`
- L91 _public prototype_ `TArrayView<const uint16> GetJointGroupJointIndices(uint16 JointGroupIndex) const override;`
- L92 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelLODs() const override;`
- L93 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelOutputIndices() const override;`
- L94 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelInputIndices() const override;`
- L95 _public prototype_ `TArrayView<const uint16> GetAnimatedMapLODs() const override;`
- L96 _public prototype_ `TArrayView<const uint16> GetAnimatedMapInputIndices() const override;`
- L97 _public prototype_ `TArrayView<const uint16> GetAnimatedMapOutputIndices() const override;`
- L98 _public prototype_ `TArrayView<const float> GetAnimatedMapFromValues() const override;`
- L99 _public prototype_ `TArrayView<const float> GetAnimatedMapToValues() const override;`
- L100 _public prototype_ `TArrayView<const float> GetAnimatedMapSlopeValues() const override;`
- L101 _public prototype_ `TArrayView<const float> GetAnimatedMapCutValues() const override;`
- L103 _public prototype_ `uint32 GetVertexPositionCount(uint16 MeshIndex) const override;` — Geometry
- L104 _public prototype_ `FVector GetVertexPosition(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L105 _public prototype_ `TArrayView<const float> GetVertexPositionXs(uint16 MeshIndex) const override;`
- L106 _public prototype_ `TArrayView<const float> GetVertexPositionYs(uint16 MeshIndex) const override;`
- L107 _public prototype_ `TArrayView<const float> GetVertexPositionZs(uint16 MeshIndex) const override;`
- L108 _public prototype_ `uint32 GetVertexTextureCoordinateCount(uint16 MeshIndex) const override;`
- L109 _public prototype_ `FTextureCoordinate GetVertexTextureCoordinate(uint16 MeshIndex, uint32 TextureCoordinateIndex) const override;`
- L110 _public prototype_ `uint32 GetVertexNormalCount(uint16 MeshIndex) const override;`
- L111 _public prototype_ `FVector GetVertexNormal(uint16 MeshIndex, uint32 NormalIndex) const override;`
- L112 _public prototype_ `uint32 GetFaceCount(uint16 MeshIndex) const override;`
- L113 _public prototype_ `TArrayView<const uint32> GetFaceVertexLayoutIndices(uint16 MeshIndex, uint32 FaceIndex) const override;`
- L114 _public prototype_ `uint32 GetVertexLayoutCount(uint16 MeshIndex) const override;`
- L115 _public prototype_ `FVertexLayout GetVertexLayout(uint16 MeshIndex, uint32 LayoutIndex) const override;`
- L116 _public prototype_ `uint16 GetMaximumInfluencePerVertex(uint16 MeshIndex) const override;`
- L117 _public prototype_ `uint32 GetSkinWeightsCount(uint16 MeshIndex) const override;`
- L118 _public prototype_ `TArrayView<const float> GetSkinWeightsValues(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L119 _public prototype_ `TArrayView<const uint16> GetSkinWeightsJointIndices(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L120 _public prototype_ `uint16 GetBlendShapeTargetCount(uint16 MeshIndex) const override;`
- L121 _public prototype_ `uint16 GetBlendShapeChannelIndex(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L122 _public prototype_ `uint32 GetBlendShapeTargetDeltaCount(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L123 _public prototype_ `FVector GetBlendShapeTargetDelta(uint16 MeshIndex, uint16 BlendShapeTargetIndex, uint32 DeltaIndex) const override;`
- L124 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaXs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L125 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaYs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L126 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaZs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L127 _public prototype_ `TArrayView<const uint32> GetBlendShapeTargetVertexIndices(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L129 _public prototype_ `uint16 GetMLControlCount() const override;` — Machine Learned Behavior
- L130 _public prototype_ `FString GetMLControlName(uint16 Index) const override;`
- L131 _public prototype_ `uint16 GetNeuralNetworkCount() const override;`
- L132 _public prototype_ `uint16 GetNeuralNetworkIndexListCount() const override;`
- L133 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForLOD(uint16 LOD) const override;`
- L134 _public prototype_ `uint16 GetMeshRegionCount(uint16 MeshIndex) const override;`
- L135 _public prototype_ `FString GetMeshRegionName(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L136 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForMeshRegion(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L137 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkInputIndices(uint16 NetIndex) const override;`
- L138 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkOutputIndices(uint16 NetIndex) const override;`
- L139 _public prototype_ `uint16 GetNeuralNetworkLayerCount(uint16 NetIndex) const override;`
- L140 _public prototype_ `EActivationFunction GetNeuralNetworkLayerActivationFunction(uint16 NetIndex, uint16 LayerIndex) const override;`
- L141 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerActivationFunctionParameters(uint16 NetIndex, uint16 LayerIndex) const override;`
- L142 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerBiases(uint16 NetIndex, uint16 LayerIndex) const override;`
- L143 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerWeights(uint16 NetIndex, uint16 LayerIndex) const override;`
- L145 _public prototype_ `ETranslationRepresentation GetJointTranslationRepresentation(uint16 JointIndex) const override;` — JointBehaviorMetadataReader
- L146 _public prototype_ `ERotationRepresentation GetJointRotationRepresentation(uint16 JointIndex) const override;`
- L147 _public prototype_ `EScaleRepresentation GetJointScaleRepresentation(uint16 JointIndex) const override;`
- L149 _public prototype_ `uint16 GetRBFPoseCount() const override;` — RBFBehavior
- L150 _public prototype_ `FString GetRBFPoseName(uint16 PoseIndex) const override;`
- L151 _public prototype_ `TArrayView<const uint16> GetRBFPoseJointOutputIndices(uint16 PoseIndex) const override;`
- L152 _public prototype_ `TArrayView<const uint16> GetRBFPoseBlendShapeChannelOutputIndices(uint16 PoseIndex) const override;`
- L153 _public prototype_ `TArrayView<const uint16> GetRBFPoseAnimatedMapOutputIndices(uint16 PoseIndex) const override;`
- L154 _public prototype_ `TArrayView<const float> GetRBFPoseJointOutputValues(uint16 PoseIndex) const override;`
- L155 _public prototype_ `float GetRBFPoseScale(uint16 PoseIndex) const override;`
- L156 _public prototype_ `uint16 GetRBFPoseControlCount() const override;`
- L157 _public prototype_ `FString GetRBFPoseControlName(uint16 PoseControlIndex) const override;`
- L158 _public prototype_ `TArrayView<const uint16> GetRBFPoseInputControlIndices(uint16 PoseIndex) const override;`
- L159 _public prototype_ `TArrayView<const uint16> GetRBFPoseOutputControlIndices(uint16 PoseIndex) const override;`
- L160 _public prototype_ `TArrayView<const float> GetRBFPoseOutputControlWeights(uint16 PoseIndex) const override;`
- L161 _public prototype_ `uint16 GetRBFSolverCount() const override;`
- L162 _public prototype_ `uint16 GetRBFSolverIndexListCount() const override;`
- L163 _public prototype_ `TArrayView<const uint16> GetRBFSolverIndicesForLOD(uint16 LOD) const override;`
- L164 _public prototype_ `FString GetRBFSolverName(uint16 SolverIndex) const override;`
- L165 _public prototype_ `TArrayView<const uint16> GetRBFSolverRawControlIndices(uint16 SolverIndex) const override;`
- L166 _public prototype_ `TArrayView<const uint16> GetRBFSolverPoseIndices(uint16 SolverIndex) const override;`
- L167 _public prototype_ `TArrayView<const float> GetRBFSolverRawControlValues(uint16 SolverIndex) const override;`
- L168 _public prototype_ `ERBFSolverType GetRBFSolverType(uint16 SolverIndex) const override;`
- L169 _public prototype_ `float GetRBFSolverRadius(uint16 SolverIndex) const override;`
- L170 _public prototype_ `EAutomaticRadius GetRBFSolverAutomaticRadius(uint16 SolverIndex) const override;`
- L171 _public prototype_ `float GetRBFSolverWeightThreshold(uint16 SolverIndex) const override;`
- L172 _public prototype_ `ERBFDistanceMethod GetRBFSolverDistanceMethod(uint16 SolverIndex) const override;`
- L173 _public prototype_ `ERBFNormalizeMethod GetRBFSolverNormalizeMethod(uint16 SolverIndex) const override;`
- L174 _public prototype_ `ERBFFunctionType GetRBFSolverFunctionType(uint16 SolverIndex) const override;`
- L175 _public prototype_ `ETwistAxis GetRBFSolverTwistAxis(uint16 SolverIndex) const override;`
- L177 _public prototype_ `uint16 GetTwistCount() const override;` — TwistSwingBehavior
- L178 _public prototype_ `ETwistAxis GetTwistSetupTwistAxis(uint16 TwistIndex) const override;`
- L179 _public prototype_ `TArrayView<const uint16> GetTwistInputControlIndices(uint16 TwistIndex) const override;`
- L180 _public prototype_ `TArrayView<const uint16> GetTwistOutputJointIndices(uint16 TwistIndex) const override;`
- L181 _public prototype_ `TArrayView<const float> GetTwistBlendWeights(uint16 TwistIndex) const override;`
- L182 _public prototype_ `uint16 GetSwingCount() const override;`
- L183 _public prototype_ `ETwistAxis GetSwingSetupTwistAxis(uint16 SwingIndex) const override;`
- L184 _public prototype_ `TArrayView<const uint16> GetSwingInputControlIndices(uint16 SwingIndex) const override;`
- L185 _public prototype_ `TArrayView<const uint16> GetSwingOutputJointIndices(uint16 SwingIndex) const override;`
- L186 _public prototype_ `TArrayView<const float> GetSwingBlendWeights(uint16 SwingIndex) const override;`
- L188 _public prototype_ `uint16 GetMLTypeCount() const override;` — MachineLearnedBehaviorExtReader
- L189 _public prototype_ `uint16 GetMLOperationSetCount(uint16 MLTypeIndex) const override;`
- L190 _public prototype_ `uint16 GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L191 _public prototype_ `EMachineLearnedBehaviorOperationType GetMLOperationType(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L192 _public prototype_ `TArrayView<const uint32> GetMLOperationParameters(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L193 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationSetIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L194 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L195 _public prototype_ `uint16 GetMLOperationIndexListCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L196 _public prototype_ `TArrayView<const uint16> GetMLOperationIndicesForLOD(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 LOD) const override;`
- L197 _public prototype_ `TArrayView<const uint16> GetMLJointsInputIndices() const override;`
- L198 _public prototype_ `TArrayView<const uint16> GetMLJointsOutputIndices() const override;`
- L199 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterKeys() const override;`
- L200 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterValues() const override;`
- L202 _public prototype_ `void Unload(EDNADataLayer Layer) override;`
- L204 _public prototype_ `const FDNAConfig& GetConfig() const override;`
- L207 _private prototype_ `dna::Reader* Unwrap() const override;`
- L210 _private member_ `TSharedPtr<FMemoryResource> MemoryResource;`
- L216 _private member_ `TUniquePtr<TWrappedReader, FWrappedReaderDeleter> ReaderPtr;`
- L217 _private member_ `FDNAConfig Config;`
- L221 _function_ `template <class TWrappedReader> FDNAReader<TWrappedReader>::FDNAReader(TWrappedReader* Source, const FDNAConfig& InConfig) : MemoryResource`
- L229 _function_ `template <class TWrappedReader> const FDNAConfig& FDNAReader<TWrappedReader>::GetConfig() const`
- L235 _function_ `template <class TWrappedReader> dna::Reader* FDNAReader<TWrappedReader>::Unwrap() const`
- L241 _function_ `template <class TWrappedReader> void FDNAReader<TWrappedReader>::Unload(EDNADataLayer Layer)`
- L256 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetFileFormatGeneration() const`
- L262 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetFileFormatVersion() const`
- L268 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetName() const`
- L274 _function_ `template <class TWrappedReader> EArchetype FDNAReader<TWrappedReader>::GetArchetype() const`
- L280 _function_ `template <class TWrappedReader> EGender FDNAReader<TWrappedReader>::GetGender() const`
- L286 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetAge() const`
- L292 _function_ `template <class TWrappedReader> uint32 FDNAReader<TWrappedReader>::GetMetaDataCount() const`
- L298 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetMetaDataKey(uint32 Index) const`
- L304 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetMetaDataValue(const FString& Key) const`
- L310 _function_ `template <class TWrappedReader> ETranslationUnit FDNAReader<TWrappedReader>::GetTranslationUnit() const`
- L316 _function_ `template <class TWrappedReader> ERotationUnit FDNAReader<TWrappedReader>::GetRotationUnit() const`
- L322 _function_ `template <class TWrappedReader> FCoordinateSystem FDNAReader<TWrappedReader>::GetCoordinateSystem() const`
- L334 _function_ `template <class TWrappedReader> ERotationSequence FDNAReader<TWrappedReader>::GetRotationSequence() const`
- L340 _function_ `template <class TWrappedReader> FRotationSign FDNAReader<TWrappedReader>::GetRotationSign() const`
- L351 _function_ `template <class TWrappedReader> EFaceWindingOrder FDNAReader<TWrappedReader>::GetFaceWindingOrder() const`
- L357 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetLODCount() const`
- L363 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetDBMaxLOD() const`
- L369 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetDBComplexity() const`
- L375 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetDBName() const`
- L382 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetGUIControlCount() const`
- L388 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetGUIControlName(uint16 Index) const`
- L394 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetRawControlCount() const`
- L400 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetRawControlName(uint16 Index) const`
- L406 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetJointCount() const`
- L412 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetJointName(uint16 Index) const`
- L418 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetJointIndexListCount() const`
- L424 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetJointIndicesForLOD(uint16 LOD) const`
- L431 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetJointParentIndex(uint16 Index) const`
- L437 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetBlendShapeChannelCount() const`
- L443 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetBlendShapeChannelName(uint16 Index) const`
- L449 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetBlendShapeChannelIndexListCount() const`
- L455 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetBlendShapeChannelIndicesForLOD(uint16 LOD) const`
- L462 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetAnimatedMapCount() const`
- L468 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetAnimatedMapName(uint16 Index) const`
- L474 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetAnimatedMapIndexListCount() const`
- L480 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetAnimatedMapIndicesForLOD(uint16 LOD) const`
- L487 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMeshCount() const`
- L493 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetMeshName(uint16 Index) const`
- L499 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMeshIndexListCount() const`
- L505 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetMeshIndicesForLOD(uint16 LOD) const`
- L512 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMeshBlendShapeChannelMappingCount() const`
- L518 _function_ `template <class TWrappedReader> FMeshBlendShapeChannelMapping FDNAReader<TWrappedReader>::GetMeshBlendShapeChannelMapping(uint16 Index) const`
- L525 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetMeshBlendShapeChannelMappingIndicesForLOD(uint16 LOD) const`
- L532 _function_ `template <class TWrappedReader> FVector FDNAReader<TWrappedReader>::GetNeutralJointTranslation(uint16 Index) const`
- L539 _function_ `template <class TWrappedReader> FVector FDNAReader<TWrappedReader>::GetNeutralJointRotation(uint16 Index) const`
- L546 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetGUIToRawInputIndices() const`
- L553 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetGUIToRawOutputIndices() const`
- L560 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetGUIToRawFromValues() const`
- L567 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetGUIToRawToValues() const`
- L574 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetGUIToRawSlopeValues() const`
- L581 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetGUIToRawCutValues() const`
- L588 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetPSDCount() const`
- L594 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetPSDRowIndices() const`
- L601 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetPSDColumnIndices() const`
- L608 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetPSDValues() const`
- L615 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetJointRowCount() const`
- L621 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetJointColumnCount() const`
- L627 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetJointVariableAttributeIndices(uint16 LOD) const`
- L634 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetJointGroupCount() const`
- L640 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetJointGroupLODs(uint16 JointGroupIndex) const`
- L647 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetJointGroupInputIndices(uint16 JointGroupIndex) const`
- L654 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetJointGroupOutputIndices(uint16 JointGroupIndex) const`
- L661 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetJointGroupValues(uint16 JointGroupIndex) const`
- L668 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetJointGroupJointIndices(uint16 JointGroupIndex) const`
- L675 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetBlendShapeChannelLODs() const`
- L682 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetBlendShapeChannelOutputIndices() const`
- L689 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetBlendShapeChannelInputIndices() const`
- L696 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetAnimatedMapLODs() const`
- L703 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetAnimatedMapInputIndices() const`
- L710 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetAnimatedMapOutputIndices() const`
- L717 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetAnimatedMapFromValues() const`
- L724 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetAnimatedMapToValues() const`
- L731 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetAnimatedMapSlopeValues() const`
- L738 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetAnimatedMapCutValues() const`
- L746 _function_ `template <class TWrappedReader> uint32 FDNAReader<TWrappedReader>::GetVertexPositionCount(uint16 MeshIndex) const`
- L752 _function_ `template <class TWrappedReader> FVector FDNAReader<TWrappedReader>::GetVertexPosition(uint16 MeshIndex, uint32 VertexIndex) const`
- L759 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetVertexPositionXs(uint16 MeshIndex) const`
- L766 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetVertexPositionYs(uint16 MeshIndex) const`
- L773 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetVertexPositionZs(uint16 MeshIndex) const`
- L780 _function_ `template <class TWrappedReader> uint32 FDNAReader<TWrappedReader>::GetVertexTextureCoordinateCount(uint16 MeshIndex) const`
- L786 _function_ `template <class TWrappedReader> FTextureCoordinate FDNAReader<TWrappedReader>::GetVertexTextureCoordinate(uint16 MeshIndex, uint32 TextureCoordinateIndex) const`
- L793 _function_ `template <class TWrappedReader> uint32 FDNAReader<TWrappedReader>::GetVertexNormalCount(uint16 MeshIndex) const`
- L799 _function_ `template <class TWrappedReader> FVector FDNAReader<TWrappedReader>::GetVertexNormal(uint16 MeshIndex, uint32 NormalIndex) const`
- L806 _function_ `template <class TWrappedReader> uint32 FDNAReader<TWrappedReader>::GetFaceCount(uint16 MeshIndex) const`
- L812 _function_ `template <class TWrappedReader> TArrayView<const uint32> FDNAReader<TWrappedReader>::GetFaceVertexLayoutIndices(uint16 MeshIndex, uint32 FaceIndex) const`
- L819 _function_ `template <class TWrappedReader> uint32 FDNAReader<TWrappedReader>::GetVertexLayoutCount(uint16 MeshIndex) const`
- L825 _function_ `template <class TWrappedReader> FVertexLayout FDNAReader<TWrappedReader>::GetVertexLayout(uint16 MeshIndex, uint32 LayoutIndex) const`
- L832 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMaximumInfluencePerVertex(uint16 MeshIndex) const`
- L838 _function_ `template <class TWrappedReader> uint32 FDNAReader<TWrappedReader>::GetSkinWeightsCount(uint16 MeshIndex) const`
- L844 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetSkinWeightsValues(uint16 MeshIndex, uint32 VertexIndex) const`
- L851 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetSkinWeightsJointIndices(uint16 MeshIndex, uint32 VertexIndex) const`
- L858 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetBlendShapeTargetCount(uint16 MeshIndex) const`
- L864 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetBlendShapeChannelIndex(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L870 _function_ `template <class TWrappedReader> uint32 FDNAReader<TWrappedReader>::GetBlendShapeTargetDeltaCount(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L876 _function_ `template <class TWrappedReader> FVector FDNAReader<TWrappedReader>::GetBlendShapeTargetDelta(uint16 MeshIndex, uint16 BlendShapeTargetIndex, uint32 DeltaIndex) const`
- L883 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetBlendShapeTargetDeltaXs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L890 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetBlendShapeTargetDeltaYs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L897 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetBlendShapeTargetDeltaZs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L904 _function_ `template <class TWrappedReader> TArrayView<const uint32> FDNAReader<TWrappedReader>::GetBlendShapeTargetVertexIndices(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L911 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMLControlCount() const`
- L917 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetMLControlName(uint16 Index) const`
- L923 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetNeuralNetworkCount() const`
- L929 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetNeuralNetworkIndexListCount() const`
- L935 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetNeuralNetworkIndicesForLOD(uint16 LOD) const`
- L942 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMeshRegionCount(uint16 MeshIndex) const`
- L948 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetMeshRegionName(uint16 MeshIndex, uint16 RegionIndex) const`
- L954 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetNeuralNetworkIndicesForMeshRegion(uint16 MeshIndex, uint16 RegionIndex) const`
- L961 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetNeuralNetworkInputIndices(uint16 NetIndex) const`
- L968 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetNeuralNetworkOutputIndices(uint16 NetIndex) const`
- L975 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetNeuralNetworkLayerCount(uint16 NetIndex) const`
- L981 _function_ `template <class TWrappedReader> EActivationFunction FDNAReader<TWrappedReader>::GetNeuralNetworkLayerActivationFunction(uint16 NetIndex, uint16 LayerIndex) const`
- L987 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetNeuralNetworkLayerActivationFunctionParameters(uint16 NetIndex, uint16 LayerIndex) const`
- L994 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetNeuralNetworkLayerBiases(uint16 NetIndex, uint16 LayerIndex) const`
- L1001 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetNeuralNetworkLayerWeights(uint16 NetIndex, uint16 LayerIndex) const`
- L1008 _function_ `template <class TWrappedReader> ETranslationRepresentation FDNAReader<TWrappedReader>::GetJointTranslationRepresentation(uint16 JointIndex) const`
- L1014 _function_ `template <class TWrappedReader> ERotationRepresentation FDNAReader<TWrappedReader>::GetJointRotationRepresentation(uint16 JointIndex) const`
- L1020 _function_ `template <class TWrappedReader> EScaleRepresentation FDNAReader<TWrappedReader>::GetJointScaleRepresentation(uint16 JointIndex) const`
- L1026 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetRBFPoseCount() const`
- L1032 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetRBFPoseName(uint16 PoseIndex) const`
- L1038 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetRBFPoseJointOutputIndices(uint16 PoseIndex) const`
- L1045 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetRBFPoseBlendShapeChannelOutputIndices(uint16 PoseIndex) const`
- L1052 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetRBFPoseAnimatedMapOutputIndices(uint16 PoseIndex) const`
- L1059 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetRBFPoseJointOutputValues(uint16 PoseIndex) const`
- L1066 _function_ `template <class TWrappedReader> float FDNAReader<TWrappedReader>::GetRBFPoseScale(uint16 PoseIndex) const`
- L1072 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetRBFPoseControlCount() const`
- L1078 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetRBFPoseControlName(uint16 PoseControlIndex) const`
- L1084 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetRBFPoseInputControlIndices(uint16 PoseIndex) const`
- L1091 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetRBFPoseOutputControlIndices(uint16 PoseIndex) const`
- L1098 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetRBFPoseOutputControlWeights(uint16 PoseIndex) const`
- L1105 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetRBFSolverCount() const`
- L1111 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetRBFSolverIndexListCount() const`
- L1117 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetRBFSolverIndicesForLOD(uint16 LOD) const`
- L1124 _function_ `template <class TWrappedReader> FString FDNAReader<TWrappedReader>::GetRBFSolverName(uint16 SolverIndex) const`
- L1130 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetRBFSolverRawControlIndices(uint16 SolverIndex) const`
- L1137 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetRBFSolverPoseIndices(uint16 SolverIndex) const`
- L1144 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetRBFSolverRawControlValues(uint16 SolverIndex) const`
- L1151 _function_ `template <class TWrappedReader> ERBFSolverType FDNAReader<TWrappedReader>::GetRBFSolverType(uint16 SolverIndex) const`
- L1157 _function_ `template <class TWrappedReader> float FDNAReader<TWrappedReader>::GetRBFSolverRadius(uint16 SolverIndex) const`
- L1163 _function_ `template <class TWrappedReader> EAutomaticRadius FDNAReader<TWrappedReader>::GetRBFSolverAutomaticRadius(uint16 SolverIndex) const`
- L1169 _function_ `template <class TWrappedReader> float FDNAReader<TWrappedReader>::GetRBFSolverWeightThreshold(uint16 SolverIndex) const`
- L1175 _function_ `template <class TWrappedReader> ERBFDistanceMethod FDNAReader<TWrappedReader>::GetRBFSolverDistanceMethod(uint16 SolverIndex) const`
- L1181 _function_ `template <class TWrappedReader> ERBFNormalizeMethod FDNAReader<TWrappedReader>::GetRBFSolverNormalizeMethod(uint16 SolverIndex) const`
- L1187 _function_ `template <class TWrappedReader> ERBFFunctionType FDNAReader<TWrappedReader>::GetRBFSolverFunctionType(uint16 SolverIndex) const`
- L1193 _function_ `template <class TWrappedReader> ETwistAxis FDNAReader<TWrappedReader>::GetRBFSolverTwistAxis(uint16 SolverIndex) const`
- L1199 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetTwistCount() const`
- L1205 _function_ `template <class TWrappedReader> ETwistAxis FDNAReader<TWrappedReader>::GetTwistSetupTwistAxis(uint16 TwistIndex) const`
- L1211 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetTwistInputControlIndices(uint16 TwistIndex) const`
- L1218 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetTwistOutputJointIndices(uint16 TwistIndex) const`
- L1225 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetTwistBlendWeights(uint16 TwistIndex) const`
- L1232 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetSwingCount() const`
- L1238 _function_ `template <class TWrappedReader> ETwistAxis FDNAReader<TWrappedReader>::GetSwingSetupTwistAxis(uint16 SwingIndex) const`
- L1245 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetSwingInputControlIndices(uint16 SwingIndex) const`
- L1252 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetSwingOutputJointIndices(uint16 SwingIndex) const`
- L1259 _function_ `template <class TWrappedReader> TArrayView<const float> FDNAReader<TWrappedReader>::GetSwingBlendWeights(uint16 SwingIndex) const`
- L1266 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMLTypeCount() const`
- L1272 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMLOperationSetCount(uint16 MLTypeIndex) const`
- L1278 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const`
- L1284 _function_ `template <class TWrappedReader> EMachineLearnedBehaviorOperationType FDNAReader<TWrappedReader>::GetMLOperationType(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const`
- L1290 _function_ `template <class TWrappedReader> TArrayView<const uint32> FDNAReader<TWrappedReader>::GetMLOperationParameters(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const`
- L1297 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetMLOperationDependencyOperationSetIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const`
- L1304 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetMLOperationDependencyOperationIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const`
- L1311 _function_ `template <class TWrappedReader> uint16 FDNAReader<TWrappedReader>::GetMLOperationIndexListCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const`
- L1317 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetMLOperationIndicesForLOD(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 LOD) const`
- L1324 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetMLJointsInputIndices() const`
- L1331 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetMLJointsOutputIndices() const`
- L1338 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetMLJointsParameterKeys() const`
- L1345 _function_ `template <class TWrappedReader> TArrayView<const uint16> FDNAReader<TWrappedReader>::GetMLJointsParameterValues() const`

#### struct `FDNAReader::FWrappedReaderDeleter`  
`struct FWrappedReaderDeleter`  
_L212-215_
- L214 _public prototype_ `void operator()(TWrappedReader* Pointer);`
- L247 _function_ `template <class TWrappedReader> void FDNAReader<TWrappedReader>::FWrappedReaderDeleter::operator()(TWrappedReader* Pointer)`

#### Free symbols / members of external scopes

- L343 _function_ `` (scope `FDNAReader::GetRotationSign`)

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/DNAToSkelMeshMap.h` (Public)


#### struct `FDNABlendShapeTarget`  
`struct FDNABlendShapeTarget`  
_L19-35_
- L21 _public function_ `FDNABlendShapeTarget() : MeshIndex(INDEX_NONE) , TargetIndex(INDEX_NONE)`
- L27 _public function_ `FDNABlendShapeTarget(const int16 InMeshIndex, const int16 InTargetIndex) : MeshIndex(InMeshIndex) , TargetIndex(InTargetIndex)`
- L33 _public member_ `int16 MeshIndex;`
- L34 _public member_ `int16 TargetIndex;`

#### class `FDNAToSkelMeshMap`  
`class FDNAToSkelMeshMap`  
_L38-90_
- desc: An object holding the mappings from DNA to UE indices, needed for updating a character from DNA file
- L42 _public function_ `FDNAToSkelMeshMap()`
- L48 _public prototype_ `void InitBaseMesh(IDNAReader* InSourceDNAReader, USkeletalMesh* InTargetSkeletalMesh);` — Creates vertex map between source DNA and target SkelMesh, and stores DNAReader Enough for updating neutral meshes, but not for updating joints and morphtargets; call the next method for that TODO: When ImportedModel is added to runtime, WITH_EDITORONLY_DATA should be removed
- L50 _public prototype_ `void MapJoints(IDNAReader* InDNAReader);` — Creates map for updating joints; needs to be called before playing animation on the rig
- L52 _public function_ `int32 GetMappedJointCount() const` — Number of DNA joints currently mapped to UE bone indices.
- L57 _public prototype_ `void MapMorphTargets(IDNAReader* InDNAReader);` — Creates map for updating morph targets; needs to be called before playing animation on the rig
- L61 _public prototype_ `bool InitFromDNAAsset(USkeletalMesh* InSkelMesh);` — Creates mappings between source DNA stored in DNAAsset AssetUserData attached to SkeletalMesh; Uses FSkeletalMeshDNAReader to be able to read geometry which, in this case, is NOT present in the DNAAsset
- L62 _public prototype_ `void InitVertexMap(IDNAReader* InDNAReader);`
- L65 _public function_ `int32 GetUEBoneIndex(int32 InRLJointIndex)`
- L70 _public function_ `TArray<FDNABlendShapeTarget>& GetMeshBlendShapeTargets()`
- L75 _public member_ `TArray<TArray<int32>> ImportVtxToDNAMeshIndex;`
- L76 _public member_ `TArray<TArray<int32>> ImportVtxToDNAVtxIndex;`
- L77 _public member_ `TArray<TArray<TArray<int32>>> ImportDNAVtxToUEVtxIndex;`
- L79 _public member_ `TArray<TArray<TArray<TArray<int32>>>> OverlappingVertices;` — Map for keeping all overlapping vertices for each vertex of each section of each LOD Model
- L80 _public member_ `TArray<TArray<int32>> UEVertexToSectionIndices;`
- L84 _private member_ `USkeletalMesh* TargetSkelMesh = nullptr;`
- L86 _private member_ `TArray<int32> RLJointToUEBoneIndices;` — UFC joint index to UE bone index
- L87 _private member_ `TArray<FDNABlendShapeTarget> MeshBlendShapeTargets;` — Reverse mapping.
- L88 _private member_ `TArray<uint16> DNASkinnedJointIndices;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGLOGICMODULE_API`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAToSkelMeshMap, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAToSkelMeshMap, Log, All);`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/DNAUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace trio`
- L18 _namespace_ `namespace dna`
- L26 _prototype_ `dna::DataLayer CalculateDNADataLayerBitmask(EDNADataLayer Layer);`
- L28 _prototype_ `TSharedPtr<IDNAReader> LoadDNAFromStream(dna::BoundedIOStream* Stream, const FDNAConfig& DNAConfig = {});`
- L29 _prototype_ `TSharedPtr<IDNAReader> LoadDNAFromBuffer(TArray<uint8>* DNABuffer, const FDNAConfig& DNAConfig = {});`
- L30 _prototype_ `TSharedPtr<IDNAReader> LoadDNAFromFile(const FString& Path, const FDNAConfig& DNAConfig = {});`
- L32 _prototype_ `void SaveDNAToStream(const IDNAReader* Reader, EDNADataLayer Layer, TNotNull<dna::BoundedIOStream*> Stream);`
- L33 _prototype_ `void SaveDNAToBuffer(const IDNAReader* Reader, EDNADataLayer Layer, TArray<uint8>& DNABuffer);`
- L34 _prototype_ `void SaveDNAToFile(const IDNAReader* Reader, EDNADataLayer Layer, const FString& Path);`
- L37 _prototype_ `TSharedPtr<IDNAReader> ReadDNAFromStream(dna::BoundedIOStream* Stream, const FDNAConfig& DNAConfig = {});` — To be used as legacy (returning FLegacyDNAReader)
- L38 _prototype_ `TSharedPtr<IDNAReader> ReadDNAFromFile(const FString& Path, EDNADataLayer Layer = EDNADataLayer::All, uint16_t MaxLOD = 0);`
- L39 _prototype_ `TSharedPtr<IDNAReader> ReadDNAFromFile(const FString& Path, EDNADataLayer Layer, TArrayView<uint16_t> LODs);`
- L40 _prototype_ `TSharedPtr<IDNAReader> ReadDNAFromBuffer(TArray<uint8>* DNABuffer, EDNADataLayer Layer = EDNADataLayer::All, uint16_t MaxLOD = 0);`
- L41 _prototype_ `TSharedPtr<IDNAReader> ReadDNAFromBuffer(TArray<uint8>* DNABuffer, EDNADataLayer Layer, TArrayView<uint16_t> LODs);`
- L43 _prototype_ `TArray<uint8> ReadStreamFromDNA(const IDNAReader* Reader, EDNADataLayer Layer);` — `UE_DEPRECATED(5.8, "This function has been deprecated, use SaveDNAToBuffer instead.")`
- L44 _prototype_ `void WriteDNAToFile(const IDNAReader* Reader, EDNADataLayer Layer, const FString& Path);`
- L47 _prototype_ `TObjectPtr<class UDNAAsset> LoadDNAAssetFromFile(const FString& InFilePath, UObject* InOuter, EDNADataLayer InLayer = EDNADataLayer::All);` — Creates a new DNA asset with behavior/geometry data set. FileHelper is used to load dna data from specified file
- L49 _prototype_ `TObjectPtr<class UDNAAsset> GetDNAAssetFromFile(const FString& InFilePath, UObject* InOuter, EDNADataLayer InLayer = EDNADataLayer::All);` — `UE_DEPRECATED(5.8, "Use GetDNAFromFile instead.")`
- L50 _prototype_ `TObjectPtr<class UDNA> ReadDNAAssetFromFile(const FString& InFilePath, UObject* InOuter, EDNADataLayer InLayer = EDNADataLayer::All);`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/LegacyDNAReaderAdapter.h` (Public)


#### class `FLegacyDNAReader`  
`template <class TWrappedReader> class FLegacyDNAReader : public IDNAReader`  
_L13-221_
- inherits: `IDNAReader`
- desc: Legacy DNA reader adapter performs legacy data transforms to UE's coordinate system. This is used by code such as MHC that hasn't switched to using the coordinate system functionality implemented in the low level DNA lib.
- L16 _public prototype_ `FLegacyDNAReader(TWrappedReader* Source, const FDNAConfig& InConfig);`
- L17 _public prototype_ `~FLegacyDNAReader() = default;`
- L19 _public prototype_ `FLegacyDNAReader(const FLegacyDNAReader&) = delete;`
- L20 _public prototype_ `FLegacyDNAReader& operator=(const FLegacyDNAReader&) = delete;`
- L22 _public prototype_ `FLegacyDNAReader(FLegacyDNAReader&&) = default;`
- L23 _public prototype_ `FLegacyDNAReader& operator=(FLegacyDNAReader&&) = default;`
- L26 _public prototype_ `uint16 GetFileFormatGeneration() const override;` — Header
- L27 _public prototype_ `uint16 GetFileFormatVersion() const override;`
- L29 _public prototype_ `FString GetName() const override;` — Descriptor
- L30 _public prototype_ `EArchetype GetArchetype() const override;`
- L31 _public prototype_ `EGender GetGender() const override;`
- L32 _public prototype_ `uint16 GetAge() const override;`
- L33 _public prototype_ `uint32 GetMetaDataCount() const override;`
- L34 _public prototype_ `FString GetMetaDataKey(uint32 Index) const override;`
- L35 _public prototype_ `FString GetMetaDataValue(const FString& Key) const override;`
- L36 _public prototype_ `ETranslationUnit GetTranslationUnit() const override;`
- L37 _public prototype_ `ERotationUnit GetRotationUnit() const override;`
- L38 _public prototype_ `FCoordinateSystem GetCoordinateSystem() const override;`
- L39 _public prototype_ `ERotationSequence GetRotationSequence() const override;`
- L40 _public prototype_ `FRotationSign GetRotationSign() const override;`
- L41 _public prototype_ `EFaceWindingOrder GetFaceWindingOrder() const override;`
- L42 _public prototype_ `uint16 GetLODCount() const override;`
- L43 _public prototype_ `uint16 GetDBMaxLOD() const override;`
- L44 _public prototype_ `FString GetDBComplexity() const override;`
- L45 _public prototype_ `FString GetDBName() const override;`
- L47 _public prototype_ `uint16 GetGUIControlCount() const override;` — Definition
- L48 _public prototype_ `FString GetGUIControlName(uint16 Index) const override;`
- L49 _public prototype_ `uint16 GetRawControlCount() const override;`
- L50 _public prototype_ `FString GetRawControlName(uint16 Index) const override;`
- L51 _public prototype_ `uint16 GetJointCount() const override;`
- L52 _public prototype_ `FString GetJointName(uint16 Index) const override;`
- L53 _public prototype_ `uint16 GetJointIndexListCount() const override;`
- L54 _public prototype_ `TArrayView<const uint16> GetJointIndicesForLOD(uint16 LOD) const override;`
- L55 _public prototype_ `uint16 GetJointParentIndex(uint16 Index) const override;`
- L56 _public prototype_ `uint16 GetBlendShapeChannelCount() const override;`
- L57 _public prototype_ `FString GetBlendShapeChannelName(uint16 Index) const override;`
- L58 _public prototype_ `uint16 GetBlendShapeChannelIndexListCount() const override;`
- L59 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelIndicesForLOD(uint16 LOD) const override;`
- L60 _public prototype_ `uint16 GetAnimatedMapCount() const override;`
- L61 _public prototype_ `FString GetAnimatedMapName(uint16 Index) const override;`
- L62 _public prototype_ `uint16 GetAnimatedMapIndexListCount() const override;`
- L63 _public prototype_ `TArrayView<const uint16> GetAnimatedMapIndicesForLOD(uint16 LOD) const override;`
- L64 _public prototype_ `uint16 GetMeshCount() const override;`
- L65 _public prototype_ `FString GetMeshName(uint16 Index) const override;`
- L66 _public prototype_ `uint16 GetMeshIndexListCount() const override;`
- L67 _public prototype_ `TArrayView<const uint16> GetMeshIndicesForLOD(uint16 LOD) const override;`
- L68 _public prototype_ `uint16 GetMeshBlendShapeChannelMappingCount() const override;`
- L69 _public prototype_ `FMeshBlendShapeChannelMapping GetMeshBlendShapeChannelMapping(uint16 Index) const override;`
- L70 _public prototype_ `TArrayView<const uint16> GetMeshBlendShapeChannelMappingIndicesForLOD(uint16 LOD) const override;`
- L71 _public prototype_ `FVector GetNeutralJointTranslation(uint16 Index) const override;`
- L72 _public prototype_ `FVector GetNeutralJointRotation(uint16 Index) const override;`
- L74 _public prototype_ `TArrayView<const uint16> GetGUIToRawInputIndices() const override;` — Behavior
- L75 _public prototype_ `TArrayView<const uint16> GetGUIToRawOutputIndices() const override;`
- L76 _public prototype_ `TArrayView<const float> GetGUIToRawFromValues() const override;`
- L77 _public prototype_ `TArrayView<const float> GetGUIToRawToValues() const override;`
- L78 _public prototype_ `TArrayView<const float> GetGUIToRawSlopeValues() const override;`
- L79 _public prototype_ `TArrayView<const float> GetGUIToRawCutValues() const override;`
- L80 _public prototype_ `uint16 GetPSDCount() const override;`
- L81 _public prototype_ `TArrayView<const uint16> GetPSDRowIndices() const override;`
- L82 _public prototype_ `TArrayView<const uint16> GetPSDColumnIndices() const override;`
- L83 _public prototype_ `TArrayView<const float> GetPSDValues() const override;`
- L84 _public prototype_ `uint16 GetJointRowCount() const override;`
- L85 _public prototype_ `uint16 GetJointColumnCount() const override;`
- L86 _public prototype_ `TArrayView<const uint16> GetJointVariableAttributeIndices(uint16 LOD) const override;`
- L87 _public prototype_ `uint16 GetJointGroupCount() const override;`
- L88 _public prototype_ `TArrayView<const uint16> GetJointGroupLODs(uint16 JointGroupIndex) const override;`
- L89 _public prototype_ `TArrayView<const uint16> GetJointGroupInputIndices(uint16 JointGroupIndex) const override;`
- L90 _public prototype_ `TArrayView<const uint16> GetJointGroupOutputIndices(uint16 JointGroupIndex) const override;`
- L91 _public prototype_ `TArrayView<const float> GetJointGroupValues(uint16 JointGroupIndex) const override;`
- L92 _public prototype_ `TArrayView<const uint16> GetJointGroupJointIndices(uint16 JointGroupIndex) const override;`
- L93 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelLODs() const override;`
- L94 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelOutputIndices() const override;`
- L95 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelInputIndices() const override;`
- L96 _public prototype_ `TArrayView<const uint16> GetAnimatedMapLODs() const override;`
- L97 _public prototype_ `TArrayView<const uint16> GetAnimatedMapInputIndices() const override;`
- L98 _public prototype_ `TArrayView<const uint16> GetAnimatedMapOutputIndices() const override;`
- L99 _public prototype_ `TArrayView<const float> GetAnimatedMapFromValues() const override;`
- L100 _public prototype_ `TArrayView<const float> GetAnimatedMapToValues() const override;`
- L101 _public prototype_ `TArrayView<const float> GetAnimatedMapSlopeValues() const override;`
- L102 _public prototype_ `TArrayView<const float> GetAnimatedMapCutValues() const override;`
- L104 _public prototype_ `uint32 GetVertexPositionCount(uint16 MeshIndex) const override;` — Geometry
- L105 _public prototype_ `FVector GetVertexPosition(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L106 _public prototype_ `TArrayView<const float> GetVertexPositionXs(uint16 MeshIndex) const override;`
- L107 _public prototype_ `TArrayView<const float> GetVertexPositionYs(uint16 MeshIndex) const override;`
- L108 _public prototype_ `TArrayView<const float> GetVertexPositionZs(uint16 MeshIndex) const override;`
- L109 _public prototype_ `uint32 GetVertexTextureCoordinateCount(uint16 MeshIndex) const override;`
- L110 _public prototype_ `FTextureCoordinate GetVertexTextureCoordinate(uint16 MeshIndex, uint32 TextureCoordinateIndex) const override;`
- L111 _public prototype_ `uint32 GetVertexNormalCount(uint16 MeshIndex) const override;`
- L112 _public prototype_ `FVector GetVertexNormal(uint16 MeshIndex, uint32 NormalIndex) const override;`
- L113 _public prototype_ `uint32 GetFaceCount(uint16 MeshIndex) const override;`
- L114 _public prototype_ `TArrayView<const uint32> GetFaceVertexLayoutIndices(uint16 MeshIndex, uint32 FaceIndex) const override;`
- L115 _public prototype_ `uint32 GetVertexLayoutCount(uint16 MeshIndex) const override;`
- L116 _public prototype_ `FVertexLayout GetVertexLayout(uint16 MeshIndex, uint32 LayoutIndex) const override;`
- L117 _public prototype_ `uint16 GetMaximumInfluencePerVertex(uint16 MeshIndex) const override;`
- L118 _public prototype_ `uint32 GetSkinWeightsCount(uint16 MeshIndex) const override;`
- L119 _public prototype_ `TArrayView<const float> GetSkinWeightsValues(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L120 _public prototype_ `TArrayView<const uint16> GetSkinWeightsJointIndices(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L121 _public prototype_ `uint16 GetBlendShapeTargetCount(uint16 MeshIndex) const override;`
- L122 _public prototype_ `uint16 GetBlendShapeChannelIndex(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L123 _public prototype_ `uint32 GetBlendShapeTargetDeltaCount(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L124 _public prototype_ `FVector GetBlendShapeTargetDelta(uint16 MeshIndex, uint16 BlendShapeTargetIndex, uint32 DeltaIndex) const override;`
- L125 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaXs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L126 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaYs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L127 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaZs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L128 _public prototype_ `TArrayView<const uint32> GetBlendShapeTargetVertexIndices(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L130 _public prototype_ `uint16 GetMLControlCount() const override;` — Machine Learned Behavior
- L131 _public prototype_ `FString GetMLControlName(uint16 Index) const override;`
- L132 _public prototype_ `uint16 GetNeuralNetworkCount() const override;`
- L133 _public prototype_ `uint16 GetNeuralNetworkIndexListCount() const override;`
- L134 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForLOD(uint16 LOD) const override;`
- L135 _public prototype_ `uint16 GetMeshRegionCount(uint16 MeshIndex) const override;`
- L136 _public prototype_ `FString GetMeshRegionName(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L137 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForMeshRegion(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L138 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkInputIndices(uint16 NetIndex) const override;`
- L139 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkOutputIndices(uint16 NetIndex) const override;`
- L140 _public prototype_ `uint16 GetNeuralNetworkLayerCount(uint16 NetIndex) const override;`
- L141 _public prototype_ `EActivationFunction GetNeuralNetworkLayerActivationFunction(uint16 NetIndex, uint16 LayerIndex) const override;`
- L142 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerActivationFunctionParameters(uint16 NetIndex, uint16 LayerIndex) const override;`
- L143 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerBiases(uint16 NetIndex, uint16 LayerIndex) const override;`
- L144 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerWeights(uint16 NetIndex, uint16 LayerIndex) const override;`
- L146 _public prototype_ `ETranslationRepresentation GetJointTranslationRepresentation(uint16 JointIndex) const override;` — JointBehaviorMetadataReader
- L147 _public prototype_ `ERotationRepresentation GetJointRotationRepresentation(uint16 JointIndex) const override;`
- L148 _public prototype_ `EScaleRepresentation GetJointScaleRepresentation(uint16 JointIndex) const override;`
- L150 _public prototype_ `uint16 GetRBFPoseCount() const override;` — RBFBehavior
- L151 _public prototype_ `FString GetRBFPoseName(uint16 PoseIndex) const override;`
- L152 _public prototype_ `TArrayView<const uint16> GetRBFPoseJointOutputIndices(uint16 PoseIndex) const override;`
- L153 _public prototype_ `TArrayView<const uint16> GetRBFPoseBlendShapeChannelOutputIndices(uint16 PoseIndex) const override;`
- L154 _public prototype_ `TArrayView<const uint16> GetRBFPoseAnimatedMapOutputIndices(uint16 PoseIndex) const override;`
- L155 _public prototype_ `TArrayView<const float> GetRBFPoseJointOutputValues(uint16 PoseIndex) const override;`
- L156 _public prototype_ `float GetRBFPoseScale(uint16 PoseIndex) const override;`
- L157 _public prototype_ `uint16 GetRBFPoseControlCount() const override;`
- L158 _public prototype_ `FString GetRBFPoseControlName(uint16 PoseControlIndex) const override;`
- L159 _public prototype_ `TArrayView<const uint16> GetRBFPoseInputControlIndices(uint16 PoseIndex) const override;`
- L160 _public prototype_ `TArrayView<const uint16> GetRBFPoseOutputControlIndices(uint16 PoseIndex) const override;`
- L161 _public prototype_ `TArrayView<const float> GetRBFPoseOutputControlWeights(uint16 PoseIndex) const override;`
- L162 _public prototype_ `uint16 GetRBFSolverCount() const override;`
- L163 _public prototype_ `uint16 GetRBFSolverIndexListCount() const override;`
- L164 _public prototype_ `TArrayView<const uint16> GetRBFSolverIndicesForLOD(uint16 LOD) const override;`
- L165 _public prototype_ `FString GetRBFSolverName(uint16 SolverIndex) const override;`
- L166 _public prototype_ `TArrayView<const uint16> GetRBFSolverRawControlIndices(uint16 SolverIndex) const override;`
- L167 _public prototype_ `TArrayView<const uint16> GetRBFSolverPoseIndices(uint16 SolverIndex) const override;`
- L168 _public prototype_ `TArrayView<const float> GetRBFSolverRawControlValues(uint16 SolverIndex) const override;`
- L169 _public prototype_ `ERBFSolverType GetRBFSolverType(uint16 SolverIndex) const override;`
- L170 _public prototype_ `float GetRBFSolverRadius(uint16 SolverIndex) const override;`
- L171 _public prototype_ `EAutomaticRadius GetRBFSolverAutomaticRadius(uint16 SolverIndex) const override;`
- L172 _public prototype_ `float GetRBFSolverWeightThreshold(uint16 SolverIndex) const override;`
- L173 _public prototype_ `ERBFDistanceMethod GetRBFSolverDistanceMethod(uint16 SolverIndex) const override;`
- L174 _public prototype_ `ERBFNormalizeMethod GetRBFSolverNormalizeMethod(uint16 SolverIndex) const override;`
- L175 _public prototype_ `ERBFFunctionType GetRBFSolverFunctionType(uint16 SolverIndex) const override;`
- L176 _public prototype_ `ETwistAxis GetRBFSolverTwistAxis(uint16 SolverIndex) const override;`
- L178 _public prototype_ `uint16 GetTwistCount() const override;` — TwistSwingBehavior
- L179 _public prototype_ `ETwistAxis GetTwistSetupTwistAxis(uint16 TwistIndex) const override;`
- L180 _public prototype_ `TArrayView<const uint16> GetTwistInputControlIndices(uint16 TwistIndex) const override;`
- L181 _public prototype_ `TArrayView<const uint16> GetTwistOutputJointIndices(uint16 TwistIndex) const override;`
- L182 _public prototype_ `TArrayView<const float> GetTwistBlendWeights(uint16 TwistIndex) const override;`
- L183 _public prototype_ `uint16 GetSwingCount() const override;`
- L184 _public prototype_ `ETwistAxis GetSwingSetupTwistAxis(uint16 SwingIndex) const override;`
- L185 _public prototype_ `TArrayView<const uint16> GetSwingInputControlIndices(uint16 SwingIndex) const override;`
- L186 _public prototype_ `TArrayView<const uint16> GetSwingOutputJointIndices(uint16 SwingIndex) const override;`
- L187 _public prototype_ `TArrayView<const float> GetSwingBlendWeights(uint16 SwingIndex) const override;`
- L189 _public prototype_ `uint16 GetMLTypeCount() const override;` — MachineLearnedBehaviorExtReader
- L190 _public prototype_ `uint16 GetMLOperationSetCount(uint16 MLTypeIndex) const override;`
- L191 _public prototype_ `uint16 GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L192 _public prototype_ `EMachineLearnedBehaviorOperationType GetMLOperationType(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L193 _public prototype_ `TArrayView<const uint32> GetMLOperationParameters(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L194 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationSetIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L195 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L196 _public prototype_ `uint16 GetMLOperationIndexListCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L197 _public prototype_ `TArrayView<const uint16> GetMLOperationIndicesForLOD(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 LOD) const override;`
- L198 _public prototype_ `TArrayView<const uint16> GetMLJointsInputIndices() const override;`
- L199 _public prototype_ `TArrayView<const uint16> GetMLJointsOutputIndices() const override;`
- L200 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterKeys() const override;`
- L201 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterValues() const override;`
- L203 _public prototype_ `void Unload(EDNADataLayer Layer) override;`
- L205 _public prototype_ `const FDNAConfig& GetConfig() const override;`
- L207 _public function_ `bool IsLegacyWrapped() const override`
- L210 _private prototype_ `dna::Reader* Unwrap() const override;`
- L213 _private member_ `TSharedPtr<FMemoryResource> MemoryResource;`
- L219 _private member_ `TUniquePtr<TWrappedReader, FWrappedReaderDeleter> ReaderPtr;`
- L220 _private member_ `FDNAConfig Config;`
- L224 _function_ `template <class TWrappedReader> FLegacyDNAReader<TWrappedReader>::FLegacyDNAReader(TWrappedReader* Source, const FDNAConfig& InConfig) : MemoryResource`
- L232 _function_ `template <class TWrappedReader> const FDNAConfig& FLegacyDNAReader<TWrappedReader>::GetConfig() const`
- L238 _function_ `template <class TWrappedReader> dna::Reader* FLegacyDNAReader<TWrappedReader>::Unwrap() const`
- L244 _function_ `template <class TWrappedReader> void FLegacyDNAReader<TWrappedReader>::Unload(EDNADataLayer Layer)`
- L259 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetFileFormatGeneration() const`
- L265 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetFileFormatVersion() const`
- L271 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetName() const`
- L277 _function_ `template <class TWrappedReader> EArchetype FLegacyDNAReader<TWrappedReader>::GetArchetype() const`
- L283 _function_ `template <class TWrappedReader> EGender FLegacyDNAReader<TWrappedReader>::GetGender() const`
- L289 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetAge() const`
- L295 _function_ `template <class TWrappedReader> uint32 FLegacyDNAReader<TWrappedReader>::GetMetaDataCount() const`
- L301 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetMetaDataKey(uint32 Index) const`
- L307 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetMetaDataValue(const FString& Key) const`
- L313 _function_ `template <class TWrappedReader> ETranslationUnit FLegacyDNAReader<TWrappedReader>::GetTranslationUnit() const`
- L319 _function_ `template <class TWrappedReader> ERotationUnit FLegacyDNAReader<TWrappedReader>::GetRotationUnit() const`
- L325 _function_ `template <class TWrappedReader> FCoordinateSystem FLegacyDNAReader<TWrappedReader>::GetCoordinateSystem() const`
- L337 _function_ `template <class TWrappedReader> ERotationSequence FLegacyDNAReader<TWrappedReader>::GetRotationSequence() const`
- L343 _function_ `template <class TWrappedReader> FRotationSign FLegacyDNAReader<TWrappedReader>::GetRotationSign() const`
- L354 _function_ `template <class TWrappedReader> EFaceWindingOrder FLegacyDNAReader<TWrappedReader>::GetFaceWindingOrder() const`
- L360 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetLODCount() const`
- L366 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetDBMaxLOD() const`
- L372 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetDBComplexity() const`
- L378 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetDBName() const`
- L385 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetGUIControlCount() const`
- L391 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetGUIControlName(uint16 Index) const`
- L397 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetRawControlCount() const`
- L403 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetRawControlName(uint16 Index) const`
- L409 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetJointCount() const`
- L415 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetJointName(uint16 Index) const`
- L421 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetJointIndexListCount() const`
- L427 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetJointIndicesForLOD(uint16 LOD) const`
- L434 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetJointParentIndex(uint16 Index) const`
- L440 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetBlendShapeChannelCount() const`
- L446 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetBlendShapeChannelName(uint16 Index) const`
- L452 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetBlendShapeChannelIndexListCount() const`
- L458 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetBlendShapeChannelIndicesForLOD(uint16 LOD) const`
- L465 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetAnimatedMapCount() const`
- L471 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetAnimatedMapName(uint16 Index) const`
- L477 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetAnimatedMapIndexListCount() const`
- L483 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetAnimatedMapIndicesForLOD(uint16 LOD) const`
- L490 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMeshCount() const`
- L496 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetMeshName(uint16 Index) const`
- L502 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMeshIndexListCount() const`
- L508 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetMeshIndicesForLOD(uint16 LOD) const`
- L515 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMeshBlendShapeChannelMappingCount() const`
- L521 _function_ `template <class TWrappedReader> FMeshBlendShapeChannelMapping FLegacyDNAReader<TWrappedReader>::GetMeshBlendShapeChannelMapping(uint16 Index) const`
- L528 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetMeshBlendShapeChannelMappingIndicesForLOD(uint16 LOD) const`
- L535 _function_ `template <class TWrappedReader> FVector FLegacyDNAReader<TWrappedReader>::GetNeutralJointTranslation(uint16 Index) const`
- L543 _function_ `template <class TWrappedReader> FVector FLegacyDNAReader<TWrappedReader>::GetNeutralJointRotation(uint16 Index) const`
- L551 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetGUIToRawInputIndices() const`
- L558 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetGUIToRawOutputIndices() const`
- L565 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetGUIToRawFromValues() const`
- L572 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetGUIToRawToValues() const`
- L579 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetGUIToRawSlopeValues() const`
- L586 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetGUIToRawCutValues() const`
- L593 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetPSDCount() const`
- L599 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetPSDRowIndices() const`
- L606 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetPSDColumnIndices() const`
- L613 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetPSDValues() const`
- L620 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetJointRowCount() const`
- L626 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetJointColumnCount() const`
- L632 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetJointVariableAttributeIndices(uint16 LOD) const`
- L639 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetJointGroupCount() const`
- L645 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetJointGroupLODs(uint16 JointGroupIndex) const`
- L652 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetJointGroupInputIndices(uint16 JointGroupIndex) const`
- L659 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetJointGroupOutputIndices(uint16 JointGroupIndex) const`
- L666 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetJointGroupValues(uint16 JointGroupIndex) const`
- L673 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetJointGroupJointIndices(uint16 JointGroupIndex) const`
- L680 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetBlendShapeChannelLODs() const`
- L687 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetBlendShapeChannelOutputIndices() const`
- L694 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetBlendShapeChannelInputIndices() const`
- L701 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetAnimatedMapLODs() const`
- L708 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetAnimatedMapInputIndices() const`
- L715 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetAnimatedMapOutputIndices() const`
- L722 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetAnimatedMapFromValues() const`
- L729 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetAnimatedMapToValues() const`
- L736 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetAnimatedMapSlopeValues() const`
- L743 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetAnimatedMapCutValues() const`
- L751 _function_ `template <class TWrappedReader> uint32 FLegacyDNAReader<TWrappedReader>::GetVertexPositionCount(uint16 MeshIndex) const`
- L757 _function_ `template <class TWrappedReader> FVector FLegacyDNAReader<TWrappedReader>::GetVertexPosition(uint16 MeshIndex, uint32 VertexIndex) const`
- L765 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetVertexPositionXs(uint16 MeshIndex) const`
- L773 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetVertexPositionYs(uint16 MeshIndex) const`
- L781 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetVertexPositionZs(uint16 MeshIndex) const`
- L789 _function_ `template <class TWrappedReader> uint32 FLegacyDNAReader<TWrappedReader>::GetVertexTextureCoordinateCount(uint16 MeshIndex) const`
- L795 _function_ `template <class TWrappedReader> FTextureCoordinate FLegacyDNAReader<TWrappedReader>::GetVertexTextureCoordinate(uint16 MeshIndex, uint32 TextureCoordinateIndex) const`
- L802 _function_ `template <class TWrappedReader> uint32 FLegacyDNAReader<TWrappedReader>::GetVertexNormalCount(uint16 MeshIndex) const`
- L808 _function_ `template <class TWrappedReader> FVector FLegacyDNAReader<TWrappedReader>::GetVertexNormal(uint16 MeshIndex, uint32 NormalIndex) const`
- L816 _function_ `template <class TWrappedReader> uint32 FLegacyDNAReader<TWrappedReader>::GetFaceCount(uint16 MeshIndex) const`
- L822 _function_ `template <class TWrappedReader> TArrayView<const uint32> FLegacyDNAReader<TWrappedReader>::GetFaceVertexLayoutIndices(uint16 MeshIndex, uint32 FaceIndex) const`
- L829 _function_ `template <class TWrappedReader> uint32 FLegacyDNAReader<TWrappedReader>::GetVertexLayoutCount(uint16 MeshIndex) const`
- L835 _function_ `template <class TWrappedReader> FVertexLayout FLegacyDNAReader<TWrappedReader>::GetVertexLayout(uint16 MeshIndex, uint32 LayoutIndex) const`
- L842 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMaximumInfluencePerVertex(uint16 MeshIndex) const`
- L848 _function_ `template <class TWrappedReader> uint32 FLegacyDNAReader<TWrappedReader>::GetSkinWeightsCount(uint16 MeshIndex) const`
- L854 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetSkinWeightsValues(uint16 MeshIndex, uint32 VertexIndex) const`
- L861 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetSkinWeightsJointIndices(uint16 MeshIndex, uint32 VertexIndex) const`
- L868 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetBlendShapeTargetCount(uint16 MeshIndex) const`
- L874 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetBlendShapeChannelIndex(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L880 _function_ `template <class TWrappedReader> uint32 FLegacyDNAReader<TWrappedReader>::GetBlendShapeTargetDeltaCount(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L886 _function_ `template <class TWrappedReader> FVector FLegacyDNAReader<TWrappedReader>::GetBlendShapeTargetDelta(uint16 MeshIndex, uint16 BlendShapeTargetIndex, uint32 DeltaIndex) const`
- L894 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetBlendShapeTargetDeltaXs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L902 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetBlendShapeTargetDeltaYs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L910 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetBlendShapeTargetDeltaZs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L918 _function_ `template <class TWrappedReader> TArrayView<const uint32> FLegacyDNAReader<TWrappedReader>::GetBlendShapeTargetVertexIndices(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const`
- L925 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMLControlCount() const`
- L931 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetMLControlName(uint16 Index) const`
- L937 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkCount() const`
- L943 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkIndexListCount() const`
- L949 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkIndicesForLOD(uint16 LOD) const`
- L956 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMeshRegionCount(uint16 MeshIndex) const`
- L962 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetMeshRegionName(uint16 MeshIndex, uint16 RegionIndex) const`
- L968 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkIndicesForMeshRegion(uint16 MeshIndex, uint16 RegionIndex) const`
- L975 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkInputIndices(uint16 NetIndex) const`
- L982 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkOutputIndices(uint16 NetIndex) const`
- L989 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkLayerCount(uint16 NetIndex) const`
- L995 _function_ `template <class TWrappedReader> EActivationFunction FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkLayerActivationFunction(uint16 NetIndex, uint16 LayerIndex) const`
- L1001 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkLayerActivationFunctionParameters(uint16 NetIndex, uint16 LayerIndex) const`
- L1008 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkLayerBiases(uint16 NetIndex, uint16 LayerIndex) const`
- L1015 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetNeuralNetworkLayerWeights(uint16 NetIndex, uint16 LayerIndex) const`
- L1022 _function_ `template <class TWrappedReader> ETranslationRepresentation FLegacyDNAReader<TWrappedReader>::GetJointTranslationRepresentation(uint16 JointIndex) const`
- L1028 _function_ `template <class TWrappedReader> ERotationRepresentation FLegacyDNAReader<TWrappedReader>::GetJointRotationRepresentation(uint16 JointIndex) const`
- L1034 _function_ `template <class TWrappedReader> EScaleRepresentation FLegacyDNAReader<TWrappedReader>::GetJointScaleRepresentation(uint16 JointIndex) const`
- L1040 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetRBFPoseCount() const`
- L1046 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetRBFPoseName(uint16 PoseIndex) const`
- L1052 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetRBFPoseJointOutputIndices(uint16 PoseIndex) const`
- L1059 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetRBFPoseBlendShapeChannelOutputIndices(uint16 PoseIndex) const`
- L1066 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetRBFPoseAnimatedMapOutputIndices(uint16 PoseIndex) const`
- L1073 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetRBFPoseJointOutputValues(uint16 PoseIndex) const`
- L1080 _function_ `template <class TWrappedReader> float FLegacyDNAReader<TWrappedReader>::GetRBFPoseScale(uint16 PoseIndex) const`
- L1086 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetRBFPoseControlCount() const`
- L1092 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetRBFPoseControlName(uint16 PoseControlIndex) const`
- L1098 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetRBFPoseInputControlIndices(uint16 PoseIndex) const`
- L1105 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetRBFPoseOutputControlIndices(uint16 PoseIndex) const`
- L1112 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetRBFPoseOutputControlWeights(uint16 PoseIndex) const`
- L1119 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetRBFSolverCount() const`
- L1125 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetRBFSolverIndexListCount() const`
- L1131 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetRBFSolverIndicesForLOD(uint16 LOD) const`
- L1138 _function_ `template <class TWrappedReader> FString FLegacyDNAReader<TWrappedReader>::GetRBFSolverName(uint16 SolverIndex) const`
- L1144 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetRBFSolverRawControlIndices(uint16 SolverIndex) const`
- L1151 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetRBFSolverPoseIndices(uint16 SolverIndex) const`
- L1158 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetRBFSolverRawControlValues(uint16 SolverIndex) const`
- L1165 _function_ `template <class TWrappedReader> ERBFSolverType FLegacyDNAReader<TWrappedReader>::GetRBFSolverType(uint16 SolverIndex) const`
- L1171 _function_ `template <class TWrappedReader> float FLegacyDNAReader<TWrappedReader>::GetRBFSolverRadius(uint16 SolverIndex) const`
- L1177 _function_ `template <class TWrappedReader> EAutomaticRadius FLegacyDNAReader<TWrappedReader>::GetRBFSolverAutomaticRadius(uint16 SolverIndex) const`
- L1183 _function_ `template <class TWrappedReader> float FLegacyDNAReader<TWrappedReader>::GetRBFSolverWeightThreshold(uint16 SolverIndex) const`
- L1189 _function_ `template <class TWrappedReader> ERBFDistanceMethod FLegacyDNAReader<TWrappedReader>::GetRBFSolverDistanceMethod(uint16 SolverIndex) const`
- L1195 _function_ `template <class TWrappedReader> ERBFNormalizeMethod FLegacyDNAReader<TWrappedReader>::GetRBFSolverNormalizeMethod(uint16 SolverIndex) const`
- L1201 _function_ `template <class TWrappedReader> ERBFFunctionType FLegacyDNAReader<TWrappedReader>::GetRBFSolverFunctionType(uint16 SolverIndex) const`
- L1207 _function_ `template <class TWrappedReader> ETwistAxis FLegacyDNAReader<TWrappedReader>::GetRBFSolverTwistAxis(uint16 SolverIndex) const`
- L1213 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetTwistCount() const`
- L1219 _function_ `template <class TWrappedReader> ETwistAxis FLegacyDNAReader<TWrappedReader>::GetTwistSetupTwistAxis(uint16 TwistIndex) const`
- L1225 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetTwistInputControlIndices(uint16 TwistIndex) const`
- L1232 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetTwistOutputJointIndices(uint16 TwistIndex) const`
- L1239 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetTwistBlendWeights(uint16 TwistIndex) const`
- L1246 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetSwingCount() const`
- L1252 _function_ `template <class TWrappedReader> ETwistAxis FLegacyDNAReader<TWrappedReader>::GetSwingSetupTwistAxis(uint16 SwingIndex) const`
- L1259 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetSwingInputControlIndices(uint16 SwingIndex) const`
- L1266 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetSwingOutputJointIndices(uint16 SwingIndex) const`
- L1273 _function_ `template <class TWrappedReader> TArrayView<const float> FLegacyDNAReader<TWrappedReader>::GetSwingBlendWeights(uint16 SwingIndex) const`
- L1280 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMLTypeCount() const`
- L1286 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMLOperationSetCount(uint16 MLTypeIndex) const`
- L1292 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const`
- L1298 _function_ `template <class TWrappedReader> EMachineLearnedBehaviorOperationType FLegacyDNAReader<TWrappedReader>::GetMLOperationType(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const`
- L1304 _function_ `template <class TWrappedReader> TArrayView<const uint32> FLegacyDNAReader<TWrappedReader>::GetMLOperationParameters(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const`
- L1311 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetMLOperationDependencyOperationSetIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const`
- L1318 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetMLOperationDependencyOperationIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const`
- L1325 _function_ `template <class TWrappedReader> uint16 FLegacyDNAReader<TWrappedReader>::GetMLOperationIndexListCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const`
- L1331 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetMLOperationIndicesForLOD(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 LOD) const`
- L1338 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetMLJointsInputIndices() const`
- L1345 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetMLJointsOutputIndices() const`
- L1352 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetMLJointsParameterKeys() const`
- L1359 _function_ `template <class TWrappedReader> TArrayView<const uint16> FLegacyDNAReader<TWrappedReader>::GetMLJointsParameterValues() const`

#### struct `FLegacyDNAReader::FWrappedReaderDeleter`  
`struct FWrappedReaderDeleter`  
_L215-218_
- L217 _public prototype_ `void operator()(TWrappedReader* Pointer);`
- L250 _function_ `template <class TWrappedReader> void FLegacyDNAReader<TWrappedReader>::FWrappedReaderDeleter::operator()(TWrappedReader* Pointer)`

#### Free symbols / members of external scopes

- L346 _function_ `` (scope `FLegacyDNAReader::GetRotationSign`)

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/RigInstance.h` (Public)


#### class `FRigInstance`  
`class FRigInstance`  
_L24-84_
- L27 _public prototype_ `explicit FRigInstance(FRigLogic* RigLogic);`
- L28 _public prototype_ `~FRigInstance();`
- L30 _public prototype_ `FRigInstance(const FRigInstance&) = delete;`
- L31 _public prototype_ `FRigInstance& operator=(const FRigInstance&) = delete;`
- L33 _public prototype_ `FRigInstance(FRigInstance&&) = default;`
- L34 _public prototype_ `FRigInstance& operator=(FRigInstance&&) = default;`
- L36 _public prototype_ `uint16 GetGUIControlCount() const;`
- L37 _public prototype_ `float GetGUIControl(uint16 Index) const;`
- L38 _public prototype_ `void SetGUIControl(uint16 Index, float Value);`
- L39 _public prototype_ `TArrayView<float> GetGUIControlValues();`
- L40 _public prototype_ `TArrayView<const float> GetGUIControlValues() const;`
- L42 _public prototype_ `uint16 GetRawControlCount() const;`
- L43 _public prototype_ `float GetRawControl(uint16 Index) const;`
- L44 _public prototype_ `void SetRawControl(uint16 Index, float Value);`
- L45 _public prototype_ `TArrayView<float> GetRawControlValues();`
- L46 _public prototype_ `TArrayView<const float> GetRawControlValues() const;`
- L48 _public prototype_ `uint16 GetPSDControlCount() const;`
- L49 _public prototype_ `float GetPSDControl(uint16 Index) const;`
- L50 _public prototype_ `TArrayView<const float> GetPSDControlValues() const;`
- L52 _public prototype_ `uint16 GetMLControlCount() const;`
- L53 _public prototype_ `float GetMLControl(uint16 Index) const;`
- L54 _public prototype_ `TArrayView<const float> GetMLControlValues() const;`
- L56 _public prototype_ `uint16 GetMLTypeCount() const;`
- L57 _public prototype_ `uint16 GetMLOperationSetCount(uint16 MLTypeIndex) const;`
- L58 _public prototype_ `uint16 GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const;`
- L59 _public prototype_ `TArrayView<float> GetMLMaskValues();`
- L60 _public prototype_ `TArrayView<const float> GetMLMaskValues() const;`
- L62 _public prototype_ `uint16 GetRBFControlCount() const;`
- L63 _public prototype_ `float GetRBFControl(uint16 Index) const;`
- L64 _public prototype_ `TArrayView<const float> GetRBFControlValues() const;`
- L66 _public prototype_ `TArrayView<const float> GetJointOutputs() const;`
- L67 _public prototype_ `TArrayView<const float> GetBlendShapeOutputs() const;`
- L68 _public prototype_ `TArrayView<const float> GetAnimatedMapOutputs() const;`
- L69 _public prototype_ `uint16 GetLOD() const;`
- L70 _public prototype_ `void SetLOD(uint16 LOD);`
- L74 _private prototype_ `rl4::RigInstance* Unwrap() const;`
- L77 _private member_ `TSharedPtr<FMemoryResource> MemoryResource;`
- L83 _private member_ `TUniquePtr<rl4::RigInstance, FRigInstanceDeleter> RigInstance;`

#### struct `FRigInstance::FRigInstanceDeleter`  
`struct FRigInstanceDeleter`  
_L79-82_
- L81 _public prototype_ `void operator()(rl4::RigInstance* Pointer);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGLOGICMODULE_API`
- L17 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/RigLogic.h` (Public)


#### enum `ERigLogicCalculationType`  
`enum class ERigLogicCalculationType: uint8`  
_L29-36_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `Scalar`
- L32 _public enumerator_ `SSE`
- L33 _public enumerator_ `AVX`
- L34 _public enumerator_ `NEON`
- L35 _public enumerator_ `AnyVector`

#### enum `ERigLogicFloatingPointType`  
`enum class ERigLogicFloatingPointType : uint8`  
_L39-44_
- reflection: `UENUM(BlueprintType)`
- L41 _public enumerator_ `Float`
- L42 _public enumerator_ `HalfFloat`
- L43 _public enumerator_ `Auto`

#### enum `ERigLogicTranslationType`  
`enum class ERigLogicTranslationType : uint8`  
_L47-50_
- reflection: `UENUM(BlueprintType)`
- L48 _public enumerator_ `None UMETA(Hidden)`
- L49 _public enumerator_ `Vector = 3`

#### enum `ERigLogicRotationType`  
`enum class ERigLogicRotationType : uint8`  
_L53-57_
- reflection: `UENUM(BlueprintType)`
- L54 _public enumerator_ `None UMETA(Hidden)`
- L55 _public enumerator_ `EulerAngles = 3`
- L56 _public enumerator_ `Quaternions = 4`

#### enum `ERigLogicRotationOrder`  
`enum class ERigLogicRotationOrder : uint8`  
_L60-67_
- reflection: `UENUM(BlueprintType, meta = (Deprecated = "5.8", DeprecationMessage = "The value is read from the DNA instead."))`
- L61 _public enumerator_ `XYZ`
- L62 _public enumerator_ `XZY`
- L63 _public enumerator_ `YXZ`
- L64 _public enumerator_ `YZX`
- L65 _public enumerator_ `ZXY`
- L66 _public enumerator_ `ZYX`

#### enum `ERigLogicScaleType`  
`enum class ERigLogicScaleType : uint8`  
_L70-73_
- reflection: `UENUM(BlueprintType)`
- L71 _public enumerator_ `None UMETA(Hidden)`
- L72 _public enumerator_ `Vector = 3`

#### struct `FPerPlatformERigLogicCalculationType`  
`struct FPerPlatformERigLogicCalculationType : public FPerPlatformInt`  
_L80-103_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Per Platform Calculation Type"))`
- inherits: `FPerPlatformInt`
- desc: Per-platform wrapper for ERigLogicCalculationType. Serializes as FPerPlatformInt but renders as enum dropdown in the editor.
- L84 _public function_ `FPerPlatformERigLogicCalculationType() : FPerPlatformInt(static_cast<int32>(ERigLogicCalculationType::AnyVector))`
- L88 _public function_ `explicit FPerPlatformERigLogicCalculationType(ERigLogicCalculationType InValue) : FPerPlatformInt(static_cast<int32>(InValue))`
- L92 _public function_ `ERigLogicCalculationType GetEnumValue() const`
- L98 _public function_ `ERigLogicCalculationType GetEnumValueForPlatform(FName PlatformName) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPerPlatformERigLogicCalculationType> : public TStructOpsTypeTraitsBase2<FPerPlatformERigLogicCalculationType>`  
_L106-113_
- inherits: `TStructOpsTypeTraitsBase2<FPerPlatformERigLogicCalculationType>`
- L112 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L109-111_

#### struct `FPerPlatformERigLogicFloatingPointType`  
`struct FPerPlatformERigLogicFloatingPointType : public FPerPlatformInt`  
_L120-143_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Per Platform Floating Point Type"))`
- inherits: `FPerPlatformInt`
- desc: Per-platform wrapper for ERigLogicFloatingPointType. Serializes as FPerPlatformInt but renders as enum dropdown in the editor.
- L124 _public function_ `FPerPlatformERigLogicFloatingPointType() : FPerPlatformInt(static_cast<int32>(ERigLogicFloatingPointType::Float))`
- L128 _public function_ `explicit FPerPlatformERigLogicFloatingPointType(ERigLogicFloatingPointType InValue) : FPerPlatformInt(static_cast<int32>(InValue))`
- L132 _public function_ `ERigLogicFloatingPointType GetEnumValue() const`
- L138 _public function_ `ERigLogicFloatingPointType GetEnumValueForPlatform(FName PlatformName) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPerPlatformERigLogicFloatingPointType> : public TStructOpsTypeTraitsBase2<FPerPlatformERigLogicFloatingPointType>`  
_L146-153_
- inherits: `TStructOpsTypeTraitsBase2<FPerPlatformERigLogicFloatingPointType>`
- L112 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L149-151_

#### struct `FRigLogicConfiguration`  
`struct FRigLogicConfiguration`  
_L156-326_
- reflection: `USTRUCT(BlueprintType)`
- L160 _public function_ `FRigLogicConfiguration() : CalculationTypePerPlatform(ERigLogicCalculationType::AnyVector), FloatingPointTypePerPlatform(ERigLogicFloatingPointType::Auto), EnableMultiThreadMLComputePerPlatform(true), LoadJoints(true), LoadBlendShapes(true), LoadAnimatedMaps(true), LoadMachineLearnedBehavior(true), LoadRBFBehavior(true), LoadTwistSwingBehavior(true), TranslationType(ERigLogicTranslationType::Vector), RotationType(ERigLogicRotationType::Quaternions), ScaleType(ERigLogicScaleType::Vector), TranslationPruningThreshold(0.0f), RotationPruningThreshold(0.0f), ScalePruningThreshold(0.0f)`
- L180 _public function_ `FRigLogicConfiguration(ERigLogicCalculationType CalculationType, bool LoadJoints, bool LoadBlendShapes, bool LoadAnimatedMaps, bool LoadMachineLearnedBehavior, bool LoadRBFBehavior, bool LoadTwistSwingBehavior, ERigLogicTranslationType TranslationType, ERigLogicRotationType RotationType, ERigLogicRotationOrder RotationOrder, ERigLogicScaleType ScaleType, float TranslationPruningThreshold, float RotationPruningThreshold, float ScalePruningThreshold) : CalculationTypePerPlatform(CalculationType), FloatingPointTypePerPlatform(ERigLogicFloatingPointType::Auto), EnableMultiThreadMLComputePerPlatform(true), LoadJoints(LoadJoints), LoadBlendShapes(LoadBlendShapes), LoadAnimatedMaps(LoadAnimatedMaps), LoadMachineLearnedBehavior(LoadMachineLearnedBehavior), LoadRBFBehavior(LoadRBFBehavior), LoadTwistSwingBehavior(LoadTwistSwingBehavior), TranslationType(TranslationType), RotationType(RotationType), ScaleType(ScaleType), TranslationPruningThreshold(TranslationPruningThreshold), RotationPruningThreshold(RotationPruningThreshold), ScalePruningThreshold(ScalePruningThreshold)` — `UE_DEPRECATED(5.8, "Use FRigLogicConfiguration overload.")`
- L212 _public function_ `FRigLogicConfiguration(ERigLogicCalculationType CalculationType, ERigLogicFloatingPointType FloatingPointType, bool EnableMultiThreadMLCompute, bool LoadJoints, bool LoadBlendShapes, bool LoadAnimatedMaps, bool LoadMachineLearnedBehavior, bool LoadRBFBehavior, bool LoadTwistSwingBehavior, ERigLogicTranslationType TranslationType, ERigLogicRotationType RotationType, ERigLogicScaleType ScaleType, float TranslationPruningThreshold, float RotationPruningThreshold, float ScalePruningThreshold) : CalculationTypePerPlatform(CalculationType), FloatingPointTypePerPlatform(FloatingPointType), EnableMultiThreadMLComputePerPlatform(EnableMultiThreadMLCompute), LoadJoints(LoadJoints), LoadBlendShapes(LoadBlendShapes), LoadAnimatedMaps(LoadAnimatedMaps), LoadMachineLearnedBehavior(LoadMachineLearnedBehavior), LoadRBFBehavior(LoadRBFBehavior), LoadTwistSwingBehavior(LoadTwistSwingBehavior), TranslationType(TranslationType), RotationType(RotationType), ScaleType(ScaleType), TranslationPruningThreshold(TranslationPruningThreshold), RotationPruningThreshold(RotationPruningThreshold), ScalePruningThreshold(ScalePruningThreshold)`
- L246 _public prototype_ `FRigLogicConfiguration(FRigLogicConfiguration&&) = default;`
- L247 _public prototype_ `FRigLogicConfiguration(const FRigLogicConfiguration&) = default;`
- L248 _public prototype_ `FRigLogicConfiguration& operator=(FRigLogicConfiguration&&) = default;`
- L249 _public prototype_ `FRigLogicConfiguration& operator=(const FRigLogicConfiguration&) = default;`
- L252 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L257 _public member_ `ERigLogicCalculationType CalculationType_DEPRECATED = ERigLogicCalculationType::AnyVector;` — `UE_DEPRECATED(5.8, "Use CalculationTypePerPlatform instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use CalculationTypePerPlatform instead"))` — --- Deprecated: plain enum, migrated to per-platform ---
- L261 _public member_ `FPerPlatformERigLogicCalculationType CalculationTypePerPlatform;` — `UPROPERTY(EditAnywhere, Category = "RigLogic", meta = (DisplayName = "Calculation Type"))` — --- New per-platform properties ---
- L264 _public member_ `FPerPlatformERigLogicFloatingPointType FloatingPointTypePerPlatform;` — `UPROPERTY(EditAnywhere, Category = "RigLogic", meta = (DisplayName = "Floating Point Type"))`
- L267 _public member_ `FPerPlatformBool EnableMultiThreadMLComputePerPlatform;` — `UPROPERTY(EditAnywhere, Category = "RigLogic", meta = (DisplayName = "Enable multi-thread ML Compute"))`
- L270 _public member_ `bool LoadJoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RigLogic")`
- L273 _public member_ `bool LoadBlendShapes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RigLogic")`
- L276 _public member_ `bool LoadAnimatedMaps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RigLogic")`
- L279 _public member_ `bool LoadMachineLearnedBehavior;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RigLogic")`
- L282 _public member_ `bool LoadRBFBehavior;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RigLogic")`
- L285 _public member_ `bool LoadTwistSwingBehavior;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RigLogic")`
- L288 _public member_ `ERigLogicTranslationType TranslationType;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`
- L291 _public member_ `ERigLogicRotationType RotationType;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`
- L295 _public member_ `ERigLogicRotationOrder RotationOrder_DEPRECATED;` — `UE_DEPRECATED(5.8, "The value is read from the DNA instead.")` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest, DeprecatedProperty, DeprecationMessage = "The value is read from the DNA instead."))`
- L298 _public member_ `ERigLogicScaleType ScaleType;` — `UPROPERTY(BlueprintReadOnly, Category = "RigLogic")`
- L307 _public member_ `float TranslationPruningThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RigLogic")` — The joint translation pruning threshold is used to eliminate joint translation deltas below the specified threshold from the joint matrix when the RigLogic instance is initialized. Use it with caution, as while it may reduce the amount of compute to be done, it may also erase important deltas that could introduce artifacts into the rig. A reasonably safe starting value to try translation pruning would be 0.0001f
- L316 _public member_ `float RotationPruningThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RigLogic")` — The joint rotation pruning threshold is used to eliminate joint rotation deltas below the specified threshold from the joint matrix when the RigLogic instance is initialized. Use it with caution, as while it may reduce the amount of compute to be done, it may also erase important deltas that could introduce artifacts into the rig. A reasonably safe starting value to try rotation pruning would be 0.1f
- L325 _public member_ `float ScalePruningThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RigLogic")` — The joint scale pruning threshold is used to eliminate joint scale deltas below the specified threshold from the joint matrix when the RigLogic instance is initialized. Use it with caution, as while it may reduce the amount of compute to be done, it may also erase important deltas that could introduce artifacts into the rig. A reasonably safe starting value to try scale pruning would be 0.001f

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRigLogicConfiguration> : public TStructOpsTypeTraitsBase2<FRigLogicConfiguration>`  
_L329-335_
- inherits: `TStructOpsTypeTraitsBase2<FRigLogicConfiguration>`
- L112 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L332-334_

#### class `FRigLogic`  
`class FRigLogic`  
_L337-398_
- L340 _public prototype_ `explicit FRigLogic(const IDNAReader* Reader, const FRigLogicConfiguration& Config = FRigLogicConfiguration());`
- L341 _public prototype_ `explicit FRigLogic(FArchive* Archive, const FRigLogicConfiguration& Config);`
- L342 _public prototype_ `~FRigLogic();`
- L344 _public prototype_ `FRigLogic(const FRigLogic&) = delete;`
- L345 _public prototype_ `FRigLogic& operator=(const FRigLogic&) = delete;`
- L347 _public prototype_ `FRigLogic(FRigLogic&&) = default;`
- L348 _public prototype_ `FRigLogic& operator=(FRigLogic&&) = default;`
- L350 _public prototype_ `void Dump(FArchive* Archive) const;`
- L351 _public prototype_ `const FRigLogicConfiguration& GetConfiguration() const;`
- L352 _public prototype_ `uint16 GetLODCount() const;`
- L353 _public prototype_ `TArrayView<const uint16> GetRBFSolverIndicesForLOD(uint16_t LOD) const;`
- L354 _public prototype_ `TArrayView<const uint16> GetMLOperationIndicesForLOD(uint16_t LOD, uint16_t MLTypeIndex, uint16 MLOperationSetIndex) const;`
- L355 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelIndicesForLOD(uint16_t LOD) const;`
- L356 _public prototype_ `TArrayView<const uint16> GetAnimatedMapIndicesForLOD(uint16_t LOD) const;`
- L357 _public prototype_ `TArrayView<const uint16> GetJointIndicesForLOD(uint16_t LOD) const;`
- L358 _public prototype_ `TArrayView<const float> GetNeutralJointValues() const;`
- L359 _public prototype_ `TArrayView<const uint16> GetJointVariableAttributeIndices(uint16 LOD) const;`
- L360 _public prototype_ `uint16 GetJointGroupCount() const;`
- L361 _public prototype_ `uint16 GetRBFSolverCount() const;`
- L362 _public prototype_ `uint16 GetTwistCount() const;`
- L363 _public prototype_ `uint16 GetSwingCount() const;`
- L364 _public prototype_ `uint16 GetMeshCount() const;`
- L365 _public prototype_ `uint16 GetMeshRegionCount(uint16 MeshIndex) const;`
- L366 _public prototype_ `uint16 GetMLTypeCount() const;`
- L367 _public prototype_ `uint16 GetMLOperationSetCount(uint16 MLTypeIndex) const;`
- L368 _public prototype_ `uint16 GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const;`
- L370 _public prototype_ `void MapGUIToRawControls(FRigInstance* Instance) const;`
- L371 _public prototype_ `void MapRawToGUIControls(FRigInstance* Instance) const;`
- L372 _public prototype_ `void CalculateMLControls(FRigInstance* Instance) const;`
- L373 _public prototype_ `void CalculateMLControls(FRigInstance* Instance, uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const;`
- L374 _public prototype_ `void CalculateRBFControls(FRigInstance* Instance) const;`
- L375 _public prototype_ `void CalculateRBFControls(FRigInstance* Instance, uint16 SolverIndex) const;`
- L376 _public prototype_ `void CalculatePSDControls(FRigInstance* Instance) const;`
- L377 _public prototype_ `void CalculateJoints(FRigInstance* Instance) const;`
- L378 _public prototype_ `void CalculateJoints(FRigInstance* Instance, uint16 JointGroupIndex) const;`
- L379 _public prototype_ `void CalculateBlendShapes(FRigInstance* Instance) const;`
- L380 _public prototype_ `void CalculateAnimatedMaps(FRigInstance* Instance) const;`
- L381 _public prototype_ `void Calculate(FRigInstance* Instance) const;`
- L382 _public prototype_ `void CollectCalculationStats(FRigInstance* Instance) const;`
- L386 _private prototype_ `rl4::RigLogic* Unwrap() const;`
- L389 _private member_ `TSharedPtr<rl4::MemoryResource> MemoryResource;`
- L395 _private member_ `TUniquePtr<rl4::RigLogic, FRigLogicDeleter> RigLogic;`
- L396 _private member_ `FRigLogicConfiguration Configuration;`
- L397 _private member_ `bool CachedEnableMultiThreadMLCompute;`

#### struct `FRigLogic::FRigLogicDeleter`  
`struct FRigLogicDeleter`  
_L391-394_
- L393 _public prototype_ `void operator()(rl4::RigLogic* Pointer);`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API RIGLOGICMODULE_API`
- L21 _namespace_ `namespace rl4`
- L110 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon7f23ad6e0103`)
- L150 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon7f23ad6e0203`)
- L333 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon7f23ad6e0303`)

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/RigLogicDNAReader.h` (Public)


#### class `RigLogicDNAReader`  
`class UE_DEPRECATED(5.8, "RigLogicDNAReader is obsolete and will be`  
_L11-219_
- inherits: `dna::Reader`
- L13 _public prototype_ `explicit RigLogicDNAReader(const dna::Reader* DNAReader);`
- L16 _public prototype_ `uint16 getFileFormatGeneration() const override;` — Header
- L17 _public prototype_ `uint16 getFileFormatVersion() const override;`
- L20 _public prototype_ `dna::StringView getName() const override;` — Descriptor
- L21 _public prototype_ `dna::Archetype getArchetype() const override;`
- L22 _public prototype_ `dna::Gender getGender() const override;`
- L23 _public prototype_ `uint16 getAge() const override;`
- L24 _public prototype_ `uint32 getMetaDataCount() const override;`
- L25 _public prototype_ `dna::StringView getMetaDataKey(uint32 index) const override;`
- L26 _public prototype_ `dna::StringView getMetaDataValue(const char* key) const override;`
- L27 _public prototype_ `dna::TranslationUnit getTranslationUnit() const override;`
- L28 _public prototype_ `dna::RotationUnit getRotationUnit() const override;`
- L29 _public prototype_ `dna::CoordinateSystem getCoordinateSystem() const override;`
- L30 _public prototype_ `uint16 getLODCount() const override;`
- L31 _public prototype_ `uint16 getDBMaxLOD() const override;`
- L32 _public prototype_ `dna::StringView getDBComplexity() const override;`
- L33 _public prototype_ `dna::StringView getDBName() const override;`
- L36 _public prototype_ `uint16 getGUIControlCount() const override;` — Definition
- L37 _public prototype_ `dna::StringView getGUIControlName(uint16 index) const override;`
- L38 _public prototype_ `uint16 getRawControlCount() const override;`
- L39 _public prototype_ `dna::StringView getRawControlName(uint16 index) const override;`
- L40 _public prototype_ `uint16 getJointCount() const override;`
- L41 _public prototype_ `dna::StringView getJointName(uint16 index) const override;`
- L42 _public prototype_ `uint16 getJointIndexListCount() const override;`
- L43 _public prototype_ `dna::ConstArrayView<uint16> getJointIndicesForLOD(uint16 lod) const override;`
- L44 _public prototype_ `uint16 getJointParentIndex(uint16 index) const override;`
- L45 _public prototype_ `uint16 getBlendShapeChannelCount() const override;`
- L46 _public prototype_ `dna::StringView getBlendShapeChannelName(uint16 index) const override;`
- L47 _public prototype_ `uint16 getBlendShapeChannelIndexListCount() const override;`
- L48 _public prototype_ `dna::ConstArrayView<uint16> getBlendShapeChannelIndicesForLOD(uint16 lod) const override;`
- L49 _public prototype_ `uint16 getAnimatedMapCount() const override;`
- L50 _public prototype_ `dna::StringView getAnimatedMapName(uint16 index) const override;`
- L51 _public prototype_ `uint16 getAnimatedMapIndexListCount() const override;`
- L52 _public prototype_ `dna::ConstArrayView<uint16> getAnimatedMapIndicesForLOD(uint16 lod) const override;`
- L53 _public prototype_ `uint16 getMeshCount() const override;`
- L54 _public prototype_ `dna::StringView getMeshName(uint16 index) const override;`
- L55 _public prototype_ `uint16 getMeshIndexListCount() const override;`
- L56 _public prototype_ `dna::ConstArrayView<uint16> getMeshIndicesForLOD(uint16 lod) const override;`
- L57 _public prototype_ `uint16 getMeshBlendShapeChannelMappingCount() const override;`
- L58 _public prototype_ `dna::MeshBlendShapeChannelMapping getMeshBlendShapeChannelMapping(uint16 index) const override;`
- L59 _public prototype_ `dna::ConstArrayView<uint16> getMeshBlendShapeChannelMappingIndicesForLOD(uint16 lod) const override;`
- L60 _public prototype_ `dna::Vector3 getNeutralJointTranslation(uint16 index) const override;`
- L61 _public prototype_ `dna::ConstArrayView<float> getNeutralJointTranslationXs() const override;`
- L62 _public prototype_ `dna::ConstArrayView<float> getNeutralJointTranslationYs() const override;`
- L63 _public prototype_ `dna::ConstArrayView<float> getNeutralJointTranslationZs() const override;`
- L64 _public prototype_ `dna::Vector3 getNeutralJointRotation(uint16 index) const override;`
- L65 _public prototype_ `dna::ConstArrayView<float> getNeutralJointRotationXs() const override;`
- L66 _public prototype_ `dna::ConstArrayView<float> getNeutralJointRotationYs() const override;`
- L67 _public prototype_ `dna::ConstArrayView<float> getNeutralJointRotationZs() const override;`
- L70 _public prototype_ `dna::ConstArrayView<uint16> getGUIToRawInputIndices() const override;` — Behavior
- L71 _public prototype_ `dna::ConstArrayView<uint16> getGUIToRawOutputIndices() const override;`
- L72 _public prototype_ `dna::ConstArrayView<float> getGUIToRawFromValues() const override;`
- L73 _public prototype_ `dna::ConstArrayView<float> getGUIToRawToValues() const override;`
- L74 _public prototype_ `dna::ConstArrayView<float> getGUIToRawSlopeValues() const override;`
- L75 _public prototype_ `dna::ConstArrayView<float> getGUIToRawCutValues() const override;`
- L76 _public prototype_ `uint16 getPSDCount() const override;`
- L77 _public prototype_ `dna::ConstArrayView<uint16> getPSDRowIndices() const override;`
- L78 _public prototype_ `dna::ConstArrayView<uint16> getPSDColumnIndices() const override;`
- L79 _public prototype_ `dna::ConstArrayView<float> getPSDValues() const override;`
- L80 _public prototype_ `uint16 getJointRowCount() const override;`
- L81 _public prototype_ `uint16 getJointColumnCount() const override;`
- L82 _public prototype_ `dna::ConstArrayView<uint16> getJointVariableAttributeIndices(uint16 lod) const override;`
- L83 _public prototype_ `uint16 getJointGroupCount() const override;`
- L84 _public prototype_ `dna::ConstArrayView<uint16> getJointGroupLODs(uint16 jointGroupIndex) const override;`
- L85 _public prototype_ `dna::ConstArrayView<uint16> getJointGroupInputIndices(uint16 jointGroupIndex) const override;`
- L86 _public prototype_ `dna::ConstArrayView<uint16> getJointGroupOutputIndices(uint16 jointGroupIndex) const override;`
- L87 _public prototype_ `dna::ConstArrayView<float> getJointGroupValues(uint16 jointGroupIndex) const override;`
- L88 _public prototype_ `dna::ConstArrayView<uint16> getJointGroupJointIndices(uint16 jointGroupIndex) const override;`
- L89 _public prototype_ `dna::ConstArrayView<uint16> getBlendShapeChannelLODs() const override;`
- L90 _public prototype_ `dna::ConstArrayView<uint16> getBlendShapeChannelInputIndices() const override;`
- L91 _public prototype_ `dna::ConstArrayView<uint16> getBlendShapeChannelOutputIndices() const override;`
- L92 _public prototype_ `dna::ConstArrayView<uint16> getAnimatedMapLODs() const override;`
- L93 _public prototype_ `dna::ConstArrayView<uint16> getAnimatedMapInputIndices() const override;`
- L94 _public prototype_ `dna::ConstArrayView<uint16> getAnimatedMapOutputIndices() const override;`
- L95 _public prototype_ `dna::ConstArrayView<float> getAnimatedMapFromValues() const override;`
- L96 _public prototype_ `dna::ConstArrayView<float> getAnimatedMapToValues() const override;`
- L97 _public prototype_ `dna::ConstArrayView<float> getAnimatedMapSlopeValues() const override;`
- L98 _public prototype_ `dna::ConstArrayView<float> getAnimatedMapCutValues() const override;`
- L101 _public prototype_ `uint32 getVertexPositionCount(uint16 meshIndex) const override;` — Geometry
- L102 _public prototype_ `dna::Position getVertexPosition(uint16 meshIndex, uint32 vertexIndex) const override;`
- L103 _public prototype_ `dna::ConstArrayView<float> getVertexPositionXs(uint16 meshIndex) const override;`
- L104 _public prototype_ `dna::ConstArrayView<float> getVertexPositionYs(uint16 meshIndex) const override;`
- L105 _public prototype_ `dna::ConstArrayView<float> getVertexPositionZs(uint16 meshIndex) const override;`
- L106 _public prototype_ `uint32 getVertexTextureCoordinateCount(uint16 meshIndex) const override;`
- L107 _public prototype_ `dna::TextureCoordinate getVertexTextureCoordinate(uint16 meshIndex, uint32 textureCoordinateIndex) const override;`
- L108 _public prototype_ `dna::ConstArrayView<float> getVertexTextureCoordinateUs(uint16 meshIndex) const override;`
- L109 _public prototype_ `dna::ConstArrayView<float> getVertexTextureCoordinateVs(uint16 meshIndex) const override;`
- L110 _public prototype_ `uint32 getVertexNormalCount(uint16 meshIndex) const override;`
- L111 _public prototype_ `dna::Normal getVertexNormal(uint16 meshIndex, uint32 normalIndex) const override;`
- L112 _public prototype_ `dna::ConstArrayView<float> getVertexNormalXs(uint16 meshIndex) const override;`
- L113 _public prototype_ `dna::ConstArrayView<float> getVertexNormalYs(uint16 meshIndex) const override;`
- L114 _public prototype_ `dna::ConstArrayView<float> getVertexNormalZs(uint16 meshIndex) const override;`
- L115 _public prototype_ `uint32 getVertexLayoutCount(uint16 meshIndex) const override;`
- L116 _public prototype_ `dna::VertexLayout getVertexLayout(uint16 meshIndex, uint32 layoutIndex) const override;`
- L117 _public prototype_ `dna::ConstArrayView<uint32> getVertexLayoutPositionIndices(uint16 meshIndex) const override;`
- L118 _public prototype_ `dna::ConstArrayView<uint32> getVertexLayoutTextureCoordinateIndices(uint16 meshIndex) const override;`
- L119 _public prototype_ `dna::ConstArrayView<uint32> getVertexLayoutNormalIndices(uint16 meshIndex) const override;`
- L120 _public prototype_ `uint32 getFaceCount(uint16 meshIndex) const override;`
- L121 _public prototype_ `dna::ConstArrayView<uint32> getFaceVertexLayoutIndices(uint16 meshIndex, uint32 faceIndex) const override;`
- L122 _public prototype_ `uint16 getMaximumInfluencePerVertex(uint16 meshIndex) const override;`
- L123 _public prototype_ `uint32 getSkinWeightsCount(uint16 meshIndex) const override;`
- L124 _public prototype_ `dna::ConstArrayView<float> getSkinWeightsValues(uint16 meshIndex, uint32 vertexIndex) const override;`
- L125 _public prototype_ `dna::ConstArrayView<uint16> getSkinWeightsJointIndices(uint16 meshIndex, uint32 vertexIndex) const override;`
- L126 _public prototype_ `uint16 getBlendShapeTargetCount(uint16 meshIndex) const override;`
- L127 _public prototype_ `uint16 getBlendShapeChannelIndex(uint16 meshIndex, uint16 blendShapeTargetIndex) const override;`
- L128 _public prototype_ `uint32 getBlendShapeTargetDeltaCount(uint16 meshIndex, uint16 blendShapeTargetIndex) const override;`
- L129 _public prototype_ `dna::Delta getBlendShapeTargetDelta(uint16 meshIndex, uint16 blendShapeTargetIndex, uint32 deltaIndex) const override;`
- L130 _public prototype_ `dna::ConstArrayView<float> getBlendShapeTargetDeltaXs(uint16 meshIndex, uint16 blendShapeTargetIndex) const override;`
- L131 _public prototype_ `dna::ConstArrayView<float> getBlendShapeTargetDeltaYs(uint16 meshIndex, uint16 blendShapeTargetIndex) const override;`
- L132 _public prototype_ `dna::ConstArrayView<float> getBlendShapeTargetDeltaZs(uint16 meshIndex, uint16 blendShapeTargetIndex) const override;`
- L133 _public prototype_ `dna::ConstArrayView<uint32> getBlendShapeTargetVertexIndices(uint16 meshIndex, uint16 blendShapeTargetIndex) const override;`
- L136 _public prototype_ `uint16 getMLControlCount() const override;` — Machine Learned Behavior
- L137 _public prototype_ `dna::StringView getMLControlName(uint16 index) const override;`
- L138 _public prototype_ `uint16 getNeuralNetworkCount() const override;`
- L139 _public prototype_ `uint16 getNeuralNetworkIndexListCount() const override;`
- L140 _public prototype_ `dna::ConstArrayView<uint16> getNeuralNetworkIndicesForLOD(uint16 lod) const override;`
- L141 _public prototype_ `uint16 getMeshRegionCount(uint16 meshIndex) const override;`
- L142 _public prototype_ `dna::StringView getMeshRegionName(uint16 meshIndex, uint16 regionIndex) const override;`
- L143 _public prototype_ `dna::ConstArrayView<uint16> getNeuralNetworkIndicesForMeshRegion(uint16 meshIndex, uint16 regionIndex) const override;`
- L144 _public prototype_ `dna::ConstArrayView<uint16> getNeuralNetworkInputIndices(uint16 netIndex) const override;`
- L145 _public prototype_ `dna::ConstArrayView<uint16> getNeuralNetworkOutputIndices(uint16 netIndex) const override;`
- L146 _public prototype_ `uint16 getNeuralNetworkLayerCount(uint16 netIndex) const override;`
- L147 _public prototype_ `dna::ActivationFunction getNeuralNetworkLayerActivationFunction(uint16 netIndex, uint16 layerIndex) const override;`
- L148 _public prototype_ `dna::ConstArrayView<float> getNeuralNetworkLayerActivationFunctionParameters(uint16 netIndex, uint16 layerIndex) const override;`
- L149 _public prototype_ `dna::ConstArrayView<float> getNeuralNetworkLayerBiases(uint16 netIndex, uint16 layerIndex) const override;`
- L150 _public prototype_ `dna::ConstArrayView<float> getNeuralNetworkLayerWeights(uint16 netIndex, uint16 layerIndex) const override;`
- L153 _public prototype_ `uint16 getRBFPoseCount() const override;` — RBFBehaviorReader methods
- L154 _public prototype_ `dna::StringView getRBFPoseName(uint16 poseIndex) const override;`
- L155 _public prototype_ `dna::ConstArrayView<uint16> getRBFPoseJointOutputIndices(uint16 poseIndex) const override;`
- L156 _public prototype_ `dna::ConstArrayView<uint16> getRBFPoseBlendShapeChannelOutputIndices(uint16 poseIndex) const override;`
- L157 _public prototype_ `dna::ConstArrayView<uint16> getRBFPoseAnimatedMapOutputIndices(uint16 poseIndex) const override;`
- L158 _public prototype_ `dna::ConstArrayView<float> getRBFPoseJointOutputValues(uint16 poseIndex) const override;`
- L159 _public prototype_ `float getRBFPoseScale(uint16 poseIndex) const override;`
- L160 _public prototype_ `uint16 getRBFPoseControlCount() const override;`
- L161 _public prototype_ `dna::StringView getRBFPoseControlName(uint16 poseControlIndex) const override;`
- L162 _public prototype_ `dna::ConstArrayView<uint16> getRBFPoseInputControlIndices(uint16 poseIndex) const override;`
- L163 _public prototype_ `dna::ConstArrayView<uint16> getRBFPoseOutputControlIndices(uint16 poseIndex) const override;`
- L164 _public prototype_ `dna::ConstArrayView<float> getRBFPoseOutputControlWeights(uint16 poseIndex) const override;`
- L165 _public prototype_ `uint16 getRBFSolverCount() const override;`
- L166 _public prototype_ `uint16 getRBFSolverIndexListCount() const override;`
- L167 _public prototype_ `dna::ConstArrayView<uint16> getRBFSolverIndicesForLOD(uint16 lod) const override;`
- L168 _public prototype_ `dna::StringView getRBFSolverName(uint16 solverIndex) const override;`
- L169 _public prototype_ `dna::ConstArrayView<uint16> getRBFSolverRawControlIndices(uint16 solverIndex) const override;`
- L170 _public prototype_ `dna::ConstArrayView<uint16> getRBFSolverPoseIndices(uint16 solverIndex) const override;`
- L171 _public prototype_ `dna::ConstArrayView<float> getRBFSolverRawControlValues(uint16 solverIndex) const override;`
- L172 _public prototype_ `dna::RBFSolverType getRBFSolverType(uint16 solverIndex) const override;`
- L173 _public prototype_ `float getRBFSolverRadius(uint16 solverIndex) const override;`
- L174 _public prototype_ `dna::AutomaticRadius getRBFSolverAutomaticRadius(uint16 solverIndex) const override;`
- L175 _public prototype_ `float getRBFSolverWeightThreshold(uint16 solverIndex) const override;`
- L176 _public prototype_ `dna::RBFDistanceMethod getRBFSolverDistanceMethod(uint16 solverIndex) const override;`
- L177 _public prototype_ `dna::RBFNormalizeMethod getRBFSolverNormalizeMethod(uint16 solverIndex) const override;`
- L178 _public prototype_ `dna::RBFFunctionType getRBFSolverFunctionType(uint16 solverIndex) const override;`
- L179 _public prototype_ `dna::TwistAxis getRBFSolverTwistAxis(uint16 solverIndex) const override;`
- L182 _public prototype_ `dna::TranslationRepresentation getJointTranslationRepresentation(uint16 jointIndex) const override;` — JointBehaviorMetadataReader methods
- L183 _public prototype_ `dna::RotationRepresentation getJointRotationRepresentation(uint16 jointIndex) const override;`
- L184 _public prototype_ `dna::ScaleRepresentation getJointScaleRepresentation(uint16 jointIndex) const override;`
- L187 _public prototype_ `uint16 getTwistCount() const override;` — TwistSwingBehaviorReader methods
- L188 _public prototype_ `dna::TwistAxis getTwistSetupTwistAxis(uint16 twistIndex) const override;`
- L189 _public prototype_ `dna::ConstArrayView<uint16> getTwistInputControlIndices(uint16 twistIndex) const override;`
- L190 _public prototype_ `dna::ConstArrayView<uint16> getTwistOutputJointIndices(uint16 twistIndex) const override;`
- L191 _public prototype_ `dna::ConstArrayView<float> getTwistBlendWeights(uint16 twistIndex) const override;`
- L192 _public prototype_ `uint16 getSwingCount() const override;`
- L193 _public prototype_ `dna::TwistAxis getSwingSetupTwistAxis(uint16 swingIndex) const override;`
- L194 _public prototype_ `dna::ConstArrayView<uint16> getSwingInputControlIndices(uint16 swingIndex) const override;`
- L195 _public prototype_ `dna::ConstArrayView<uint16> getSwingOutputJointIndices(uint16 swingIndex) const override;`
- L196 _public prototype_ `dna::ConstArrayView<float> getSwingBlendWeights(uint16 swingIndex) const override;`
- L199 _public prototype_ `uint16 getMLTypeCount() const override;` — MachineLearnedBehaviorExtReader methods
- L200 _public prototype_ `uint16 getMLOperationSetCount(uint16 mlTypeIndex) const override;`
- L201 _public prototype_ `uint16 getMLOperationCount(uint16 mlTypeIndex, uint16 mlOperationSetIndex) const override;`
- L202 _public prototype_ `dna::MachineLearnedBehaviorOperationType getMLOperationType(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 mlOperationIndex) const override;`
- L203 _public prototype_ `dna::ConstArrayView<uint32> getMLOperationParameters(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 mlOperationIndex) const override;`
- L204 _public prototype_ `dna::ConstArrayView<uint16> getMLOperationDependencyOperationSetIndices(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 mlOperationIndex) const override;`
- L205 _public prototype_ `dna::ConstArrayView<uint16> getMLOperationDependencyOperationIndices(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 mlOperationIndex) const override;`
- L206 _public prototype_ `uint16 getMLOperationIndexListCount(uint16 mlTypeIndex, uint16 mlOperationSetIndex) const override;`
- L207 _public prototype_ `dna::ConstArrayView<uint16> getMLOperationIndicesForLOD(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 lod) const override;`
- L208 _public prototype_ `dna::ConstArrayView<uint16> getMLJointsInputIndices() const override;`
- L209 _public prototype_ `dna::ConstArrayView<uint16> getMLJointsOutputIndices() const override;`
- L210 _public prototype_ `dna::ConstArrayView<uint16> getMLJointsParameterKeys() const override;`
- L211 _public prototype_ `dna::ConstArrayView<uint16> getMLJointsParameterValues() const override;`
- L214 _public prototype_ `void unload(dna::DataLayer Layer) override;` — Reader
- L215 _public prototype_ `static void destroy(dna::Reader* Pointer);`
- L218 _private member_ `const dna::Reader* Reader;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGLOGICMODULE_API`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/RigLogicModule.h` (Public)


#### class `FRigLogicModule`  
`class FRigLogicModule: public IModuleInterface`  
_L39-44_
- inherits: `IModuleInterface`
- L42 _public prototype_ `void StartupModule() override;`
- L43 _public prototype_ `void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGLOGICMODULE_API`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogic, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogic, Log, All);`
- L14 _delegate_ `DECLARE_STATS_GROUP(TEXT("RigLogic"), STATGROUP_RigLogic, STATCAT_Advanced) DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Calculation Backend [ 0 = Scalar, 1 = SSE, 2 = AVX, 3 = NEON ]"), STAT_RigL`
- L16 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Calculation Backend [ 0 = Scalar, 1 = SSE, 2 = AVX, 3 = NEON ]"), STAT_RigL`
- L17 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Floating Point Type [ 0 = Float, 1 = Half-Float ]"), STAT_RigLogic_FloatingPo`
- L18 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Multi-thread ML Compute [ 0 = False, 1 = True ]"), STAT_RigLogic_MultiThreadMLCo`
- L19 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Current LOD"), STAT_RigLogic_LOD, STATGROUP_RigLogic, RIGLOGICM`
- L20 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("RBF Solver Count"), STAT_RigLogic_RBFSolverCount, STATGROUP_RigLogic, RIGL`
- L21 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("ML Operation Count"), STAT_RigLogic_MLOperationCount, STATGROUP_RigLogic, RI`
- L22 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("PSD Expression Count"), STAT_RigLogic_PSDCount, STATGROUP_RigLogic,`
- L23 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Joint Count"), STAT_RigLogic_JointCount, STATGROUP_RigLogic, RIGLOGICM`
- L24 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Joint Delta Value Count"), STAT_RigLogic_JointDeltaValueCount, STATGROUP_RigLogi`
- L25 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Blend Shape Channel Count"), STAT_RigLogic_BlendShapeChannelCount, STATGROUP_RigLo`
- L26 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Animated Map Count"), STAT_RigLogic_AnimatedMapCount, STATGROUP_RigLogic, RI`
- L27 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Vertex Count"), STAT_RigLogic_VertexCount, STATGROUP_RigLogic, RIGLOGIC`
- L29 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Map GUI To Raw Controls Time"), STAT_RigLogic_MapGUIToRawControlsTime, STATGROUP_Ri`
- L30 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Map Raw To GUI Controls Time"), STAT_RigLogic_MapRawToGUIControlsTime, STATGROUP_Ri`
- L31 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Calculate RBF Controls Time"), STAT_RigLogic_CalculateRBFControlsTime, STATGROUP_Rig`
- L32 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Calculate ML Controls Time"), STAT_RigLogic_CalculateMLControlsTime, STATGROUP_RigL`
- L33 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Calculate PSD Controls Time"), STAT_RigLogic_CalculatePSDControlsTime, STATGROUP_Rig`
- L34 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Calculate Joints Time"), STAT_RigLogic_CalculateJointsTime, STATGROUP_RigLogic,`
- L35 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Calculate Blend Shapes Time"), STAT_RigLogic_CalculateBlendShapesTime, STATGROUP_Rig`
- L36 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Calculate Animated Maps Time"), STAT_RigLogic_CalculateAnimatedMapsTime, STATGROUP_Ri`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/RigUnit_RigLogic.h` (Public)


#### struct `FBoneIndexControlAttributeMapping`  
`struct FBoneIndexControlAttributeMapping`  
_L21-31_
- reflection: `USTRUCT(meta = (DocumentationPolicy = "Strict"))`
- desc: A helper struct used inside of the RigUnit_RigLogic to map bone indices to DNA driver joint indices.
- L25 _public member_ `int32 BoneIndex;`
- L26 _public member_ `int32 DNAJointIndex;`
- L27 _public member_ `int32 RotationX;`
- L28 _public member_ `int32 RotationY;`
- L29 _public member_ `int32 RotationZ;`
- L30 _public member_ `int32 RotationW;`

#### struct `FRigUnit_RigLogic_IntArray`  
`struct FRigUnit_RigLogic_IntArray`  
_L35-42_
- reflection: `USTRUCT(meta = (DocumentationPolicy = "Strict"))`
- desc: A helper struct used inside of the RigUnit_RigLogic to store arrays of arrays of integers.
- L41 _public member_ `TArray<int32> Values;` — `UPROPERTY(transient)` — The values stored within this array.

#### struct `FRigUnit_RigLogic_IntMatrix`  
`struct FRigUnit_RigLogic_IntMatrix`  
_L46-53_
- reflection: `USTRUCT(meta = (DocumentationPolicy = "Strict"))`
- desc: A helper struct used inside of the RigUnit_RigLogic to store arrays of arrays of integers.
- L52 _public member_ `TArray<FRigUnit_RigLogic_IntArray> Values;` — `UPROPERTY(transient)` — The values stored within this array.

#### struct `FRigUnit_RigLogic_Data`  
`struct FRigUnit_RigLogic_Data`  
_L57-146_
- reflection: `USTRUCT(meta = (DocumentationPolicy = "Strict"))`
- desc: The work data used by the FRigUnit_RigLogic
- L61 _public prototype_ `FRigUnit_RigLogic_Data();`
- L62 _public prototype_ `~FRigUnit_RigLogic_Data();`
- L63 _public prototype_ `FRigUnit_RigLogic_Data(const FRigUnit_RigLogic_Data& Other);`
- L64 _public prototype_ `FRigUnit_RigLogic_Data& operator=(const FRigUnit_RigLogic_Data& Other);`
- L68 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkelMeshComponent;` — `UPROPERTY(transient)` — Cached Skeletal Mesh Component
- L70 _public member_ `TSharedPtr<FSharedRigRuntimeContext> LocalRigRuntimeContext;`
- L76 _public member_ `TUniquePtr<FRigInstance> RigInstance;` — RigInstance is a thin class, containing only character instance specific data i.e. the output buffers where RigLogic writes the results of computations, specific to each instance of a rig.
- L85 _public member_ `TArray<int32> InputCurveIndices;` — `UPROPERTY(transient)` — RL input index to ControlRig's input curve index
- L89 _public member_ `TArray<int32> MLMaskCurveIndices;` — `UPROPERTY(transient)` — RL neural network mask index to ControlRig's input curve index
- L93 _public member_ `TArray<int32> HierarchyBoneIndices;` — `UPROPERTY(transient)` — RL joint index to ControlRig's hierarchy bone index
- L97 _public member_ `TArray<FBoneIndexControlAttributeMapping> DriverJointsToControlAttributesMap;` — `UPROPERTY(transient)` — RL driver joint index to ControlRig's hierarchy bone index and RigLogic control attribute mapping
- L101 _public member_ `TArray<FRigUnit_RigLogic_IntArray> MorphTargetCurveIndices;` — `UPROPERTY(transient)` — RL mesh blend shape index to ControlRig's output blendshape curve index for each LOD
- L105 _public member_ `TArray<FRigUnit_RigLogic_IntArray> BlendShapeIndices;` — `UPROPERTY(transient)` — RL mesh+blend shape array index to RL blend shape index for each LOD
- L109 _public member_ `TArray<FRigUnit_RigLogic_IntArray> CurveElementIndicesForAnimMaps;` — `UPROPERTY(transient)` — RL animated map index to ControlRig's output anim map curve index for each LOD
- L113 _public member_ `TArray<FRigUnit_RigLogic_IntArray> RigLogicIndicesForAnimMaps;` — `UPROPERTY(transient)` — RL animated map index to RL anim map curve index for each LOD
- L117 _public member_ `uint32 CurrentLOD;` — `UPROPERTY(transient)` — LOD for which the model is rendered
- L119 _public member_ `static const uint8 MAX_ATTRS_PER_JOINT;`
- L121 _public prototype_ `bool IsRigLogicInitialized();`
- L122 _public prototype_ `void InitializeRigLogic(const URigHierarchy* InHierarchy, TSharedPtr<FSharedRigRuntimeContext> NewContext);`
- L125 _public prototype_ `void MapInputCurveIndices(const URigHierarchy* InHierarchy);` — Makes a map of input curve indices from DNA file to the control rig curves
- L127 _public prototype_ `void MapMLMaskCurveIndices(const URigHierarchy* InHierarchy);` — Makes a map of neural net mask indices from DNA file to the control rig curves
- L129 _public prototype_ `void MapJoints(const URigHierarchy* Hierarchy);` — Uses names to map joint indices from DNA file to the indices of bones in control rig hierarchy
- L130 _public prototype_ `void MapDriverJoints(const URigHierarchy* Hierarchy);`
- L133 _public prototype_ `void MapMorphTargets(const URigHierarchy* InHierarchy);` — Uses names of blend shapes and meshes in DNA file, for all LODs, to map their indices to the indices of morph target curves in the curve container; curve name format is <mesh>__<blendshape>
- L136 _public prototype_ `void MapMaskMultipliers(const URigHierarchy* InHierarchy);` — Uses names to map mask multiplier indices from DNA file, for all LODs, to the indices of curves in the control rig's curve container
- L139 _public prototype_ `void CalculateRigLogic(const URigHierarchy* InHierarchy, TArrayView<const float> NeutralJointValues);` — Calculates joint positions, orientation and scale based on inputs curves of the control rig
- L141 _public prototype_ `void UpdateJoints(URigHierarchy* Hierarchy, TArrayView<const float> NeutralJointValues, TArrayView<const float> DeltaJointValues);` — Updates joint positions in the hierarchy based on inputs curves of the control rig
- L143 _public prototype_ `void UpdateBlendShapeCurves(URigHierarchy* InHierarchy, TArrayView<const float> BlendShapeValues);` — Updates morph target curve values based on values of input curves of the control rig
- L145 _public prototype_ `void UpdateAnimMapCurves(URigHierarchy* InHierarchy, TArrayView<const float> AnimMapOutputs);` — Updates anim map curve values based on values of input curves of the control rig

#### struct `FRigUnit_RigLogic`  
`struct FRigUnit_RigLogic: public FRigUnitMutable`  
_L153-183_
- reflection: `USTRUCT(meta = (DisplayName = "RigLogic", Category = "RigLogic", DocumentationPolicy = "Strict", Keywords = "Rig,RigLogic"))`
- inherits: `FRigUnitMutable`
- L157 _public function_ `FRigUnit_RigLogic() : Data() , bIsInitialized(false)`
- L169 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L173 _private prototype_ `static TSharedPtr<FSharedRigRuntimeContext> GetSharedRigRuntimeContext(USkeletalMesh* SkelMesh);`
- L178 _private member_ `FRigUnit_RigLogic_Data Data;` — `UPROPERTY(transient)` — internal work data for the unit
- L182 _private member_ `bool bIsInitialized;` — `UPROPERTY(transient)` — flag to determine if the node has been initialized

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicUnit, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicUnit, Log, All);`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/SharedRigRuntimeContext.h` (Public)


#### struct `FSharedRigRuntimeContext`  
`struct FSharedRigRuntimeContext`  
_L9-38_
- L18 _public member_ `TSharedPtr<IDNAReader> DNAReader;` — Redundant but stored here as well so the runtime context can be updated / queried atomically
- L23 _public member_ `TSharedPtr<FRigLogic> RigLogic;` — RigLogic itself is stateless, and is designed to be shared between multiple rig instances based on the same DNA.
- L26 _public member_ `TArray<TNestedArray<uint16>> VariableJointIndicesPerLOD;` — Cached joint indices that need to be updated for each LOD
- L28 _public member_ `TArray<FQuat> InverseNeutralJointRotations;`
- L32 _public prototype_ `FSharedRigRuntimeContext();` — `UE_DEPRECATED(5.8, "Default constructor is deprecated. Use the explicit constructor instead.")` — Deprecated default constructor for ABI compatibility
- L34 _public prototype_ `FSharedRigRuntimeContext(TSharedPtr<IDNAReader> InBehaviorReader, TSharedPtr<FRigLogic> InRigLogic);`
- L35 _public prototype_ `void CacheVariableJointIndices();`
- L36 _public prototype_ `void CacheInverseNeutralJointRotations();`

#### struct `FSharedRigRuntimeContext::TNestedArray`  
`template <typename T> struct TNestedArray`  
_L12-15_
- L14 _public member_ `TArray<T> Values;`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/SkelMeshDNAReader.h` (Public)


#### class `FSkelMeshDNAReader`  
`class UE_DEPRECATED(5.8, "FSkelMeshDNAReader is obsolete and will be removed. FDNAReader can be used instead. Delete any usages.") FSkelMeshDNAReader: public IDNAReader`  
_L22-215_
- inherits: `IDNAReader`
- L25 _public prototype_ `explicit FSkelMeshDNAReader(UDNAAsset* DNAAsset);`
- L28 _public prototype_ `uint16 GetFileFormatGeneration() const override;` — Header
- L29 _public prototype_ `uint16 GetFileFormatVersion() const override;`
- L31 _public prototype_ `FString GetName() const override;` — Descriptor
- L32 _public prototype_ `EArchetype GetArchetype() const override;`
- L33 _public prototype_ `EGender GetGender() const override;`
- L34 _public prototype_ `uint16 GetAge() const override;`
- L35 _public prototype_ `uint32 GetMetaDataCount() const override;`
- L36 _public prototype_ `FString GetMetaDataKey(uint32 Index) const override;`
- L37 _public prototype_ `FString GetMetaDataValue(const FString& Key) const override;`
- L38 _public prototype_ `ETranslationUnit GetTranslationUnit() const override;`
- L39 _public prototype_ `ERotationUnit GetRotationUnit() const override;`
- L40 _public prototype_ `FCoordinateSystem GetCoordinateSystem() const override;`
- L41 _public prototype_ `ERotationSequence GetRotationSequence() const override;`
- L42 _public prototype_ `FRotationSign GetRotationSign() const override;`
- L43 _public prototype_ `EFaceWindingOrder GetFaceWindingOrder() const override;`
- L44 _public prototype_ `uint16 GetLODCount() const override;`
- L45 _public prototype_ `uint16 GetDBMaxLOD() const override;`
- L46 _public prototype_ `FString GetDBComplexity() const override;`
- L47 _public prototype_ `FString GetDBName() const override;`
- L49 _public prototype_ `uint16 GetGUIControlCount() const override;` — Definition
- L50 _public prototype_ `FString GetGUIControlName(uint16 Index) const override;`
- L51 _public prototype_ `uint16 GetRawControlCount() const override;`
- L52 _public prototype_ `FString GetRawControlName(uint16 Index) const override;`
- L53 _public prototype_ `uint16 GetJointCount() const override;`
- L54 _public prototype_ `FString GetJointName(uint16 Index) const override;`
- L55 _public prototype_ `uint16 GetJointIndexListCount() const override;`
- L56 _public prototype_ `TArrayView<const uint16> GetJointIndicesForLOD(uint16 LOD) const override;`
- L57 _public prototype_ `uint16 GetJointParentIndex(uint16 Index) const override;`
- L58 _public prototype_ `uint16 GetBlendShapeChannelCount() const override;`
- L59 _public prototype_ `FString GetBlendShapeChannelName(uint16 Index) const override;`
- L60 _public prototype_ `uint16 GetBlendShapeChannelIndexListCount() const override;`
- L61 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelIndicesForLOD(uint16 LOD) const override;`
- L62 _public prototype_ `uint16 GetAnimatedMapCount() const override;`
- L63 _public prototype_ `FString GetAnimatedMapName(uint16 Index) const override;`
- L64 _public prototype_ `uint16 GetAnimatedMapIndexListCount() const override;`
- L65 _public prototype_ `TArrayView<const uint16> GetAnimatedMapIndicesForLOD(uint16 LOD) const override;`
- L66 _public prototype_ `uint16 GetMeshCount() const override;`
- L67 _public prototype_ `FString GetMeshName(uint16 Index) const override;`
- L68 _public prototype_ `uint16 GetMeshIndexListCount() const override;`
- L69 _public prototype_ `TArrayView<const uint16> GetMeshIndicesForLOD(uint16 LOD) const override;`
- L70 _public prototype_ `uint16 GetMeshBlendShapeChannelMappingCount() const override;`
- L71 _public prototype_ `FMeshBlendShapeChannelMapping GetMeshBlendShapeChannelMapping(uint16 Index) const override;`
- L72 _public prototype_ `TArrayView<const uint16> GetMeshBlendShapeChannelMappingIndicesForLOD(uint16 LOD) const override;`
- L73 _public prototype_ `FVector GetNeutralJointTranslation(uint16 Index) const override;`
- L74 _public prototype_ `FVector GetNeutralJointRotation(uint16 Index) const override;`
- L76 _public prototype_ `TArrayView<const uint16> GetGUIToRawInputIndices() const override;` — Behavior
- L77 _public prototype_ `TArrayView<const uint16> GetGUIToRawOutputIndices() const override;`
- L78 _public prototype_ `TArrayView<const float> GetGUIToRawFromValues() const override;`
- L79 _public prototype_ `TArrayView<const float> GetGUIToRawToValues() const override;`
- L80 _public prototype_ `TArrayView<const float> GetGUIToRawSlopeValues() const override;`
- L81 _public prototype_ `TArrayView<const float> GetGUIToRawCutValues() const override;`
- L82 _public prototype_ `uint16 GetPSDCount() const override;`
- L83 _public prototype_ `TArrayView<const uint16> GetPSDRowIndices() const override;`
- L84 _public prototype_ `TArrayView<const uint16> GetPSDColumnIndices() const override;`
- L85 _public prototype_ `TArrayView<const float> GetPSDValues() const override;`
- L86 _public prototype_ `uint16 GetJointRowCount() const override;`
- L87 _public prototype_ `uint16 GetJointColumnCount() const override;`
- L88 _public prototype_ `TArrayView<const uint16> GetJointVariableAttributeIndices(uint16 LOD) const override;`
- L89 _public prototype_ `uint16 GetJointGroupCount() const override;`
- L90 _public prototype_ `TArrayView<const uint16> GetJointGroupLODs(uint16 JointGroupIndex) const override;`
- L91 _public prototype_ `TArrayView<const uint16> GetJointGroupInputIndices(uint16 JointGroupIndex) const override;`
- L92 _public prototype_ `TArrayView<const uint16> GetJointGroupOutputIndices(uint16 JointGroupIndex) const override;`
- L93 _public prototype_ `TArrayView<const float> GetJointGroupValues(uint16 JointGroupIndex) const override;`
- L94 _public prototype_ `TArrayView<const uint16> GetJointGroupJointIndices(uint16 JointGroupIndex) const override;`
- L95 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelLODs() const override;`
- L96 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelOutputIndices() const override;`
- L97 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelInputIndices() const override;`
- L98 _public prototype_ `TArrayView<const uint16> GetAnimatedMapLODs() const override;`
- L99 _public prototype_ `TArrayView<const uint16> GetAnimatedMapInputIndices() const override;`
- L100 _public prototype_ `TArrayView<const uint16> GetAnimatedMapOutputIndices() const override;`
- L101 _public prototype_ `TArrayView<const float> GetAnimatedMapFromValues() const override;`
- L102 _public prototype_ `TArrayView<const float> GetAnimatedMapToValues() const override;`
- L103 _public prototype_ `TArrayView<const float> GetAnimatedMapSlopeValues() const override;`
- L104 _public prototype_ `TArrayView<const float> GetAnimatedMapCutValues() const override;`
- L106 _public prototype_ `uint32 GetVertexPositionCount(uint16 MeshIndex) const override;` — Geometry
- L107 _public prototype_ `FVector GetVertexPosition(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L108 _public prototype_ `TArrayView<const float> GetVertexPositionXs(uint16 MeshIndex) const override;`
- L109 _public prototype_ `TArrayView<const float> GetVertexPositionYs(uint16 MeshIndex) const override;`
- L110 _public prototype_ `TArrayView<const float> GetVertexPositionZs(uint16 MeshIndex) const override;`
- L111 _public prototype_ `uint32 GetVertexTextureCoordinateCount(uint16 MeshIndex) const override;`
- L112 _public prototype_ `FTextureCoordinate GetVertexTextureCoordinate(uint16 MeshIndex, uint32 TextureCoordinateIndex) const override;`
- L113 _public prototype_ `uint32 GetVertexNormalCount(uint16 MeshIndex) const override;`
- L114 _public prototype_ `FVector GetVertexNormal(uint16 MeshIndex, uint32 NormalIndex) const override;`
- L115 _public prototype_ `uint32 GetFaceCount(uint16 MeshIndex) const override;`
- L116 _public prototype_ `TArrayView<const uint32> GetFaceVertexLayoutIndices(uint16 MeshIndex, uint32 FaceIndex) const override;`
- L117 _public prototype_ `uint32 GetVertexLayoutCount(uint16 MeshIndex) const override;`
- L118 _public prototype_ `FVertexLayout GetVertexLayout(uint16 MeshIndex, uint32 LayoutIndex) const override;`
- L119 _public prototype_ `uint16 GetMaximumInfluencePerVertex(uint16 MeshIndex) const override;`
- L120 _public prototype_ `uint32 GetSkinWeightsCount(uint16 MeshIndex) const override;`
- L121 _public prototype_ `TArrayView<const float> GetSkinWeightsValues(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L122 _public prototype_ `TArrayView<const uint16> GetSkinWeightsJointIndices(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L123 _public prototype_ `uint16 GetBlendShapeTargetCount(uint16 MeshIndex) const override;`
- L124 _public prototype_ `uint16 GetBlendShapeChannelIndex(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L125 _public prototype_ `uint32 GetBlendShapeTargetDeltaCount(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L126 _public prototype_ `FVector GetBlendShapeTargetDelta(uint16 MeshIndex, uint16 BlendShapeTargetIndex, uint32 DeltaIndex) const override;`
- L127 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaXs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L128 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaYs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L129 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaZs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L130 _public prototype_ `TArrayView<const uint32> GetBlendShapeTargetVertexIndices(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L132 _public prototype_ `uint16 GetMLControlCount() const override;` — Machine Learned Behavior
- L133 _public prototype_ `FString GetMLControlName(uint16 Index) const override;`
- L134 _public prototype_ `uint16 GetNeuralNetworkCount() const override;`
- L135 _public prototype_ `uint16 GetNeuralNetworkIndexListCount() const override;`
- L136 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForLOD(uint16 LOD) const override;`
- L137 _public prototype_ `uint16 GetMeshRegionCount(uint16 MeshIndex) const override;`
- L138 _public prototype_ `FString GetMeshRegionName(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L139 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForMeshRegion(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L140 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkInputIndices(uint16 NetIndex) const override;`
- L141 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkOutputIndices(uint16 NetIndex) const override;`
- L142 _public prototype_ `uint16 GetNeuralNetworkLayerCount(uint16 NetIndex) const override;`
- L143 _public prototype_ `EActivationFunction GetNeuralNetworkLayerActivationFunction(uint16 NetIndex, uint16 LayerIndex) const override;`
- L144 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerActivationFunctionParameters(uint16 NetIndex, uint16 LayerIndex) const override;`
- L145 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerBiases(uint16 NetIndex, uint16 LayerIndex) const override;`
- L146 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerWeights(uint16 NetIndex, uint16 LayerIndex) const override;`
- L148 _public prototype_ `ETranslationRepresentation GetJointTranslationRepresentation(uint16 JointIndex) const override;` — JointBehaviorMetadataReader
- L149 _public prototype_ `ERotationRepresentation GetJointRotationRepresentation(uint16 JointIndex) const override;`
- L150 _public prototype_ `EScaleRepresentation GetJointScaleRepresentation(uint16 JointIndex) const override;`
- L152 _public prototype_ `uint16 GetRBFPoseCount() const override;` — RBFBehavior
- L153 _public prototype_ `FString GetRBFPoseName(uint16 PoseIndex) const override;`
- L154 _public prototype_ `TArrayView<const uint16> GetRBFPoseJointOutputIndices(uint16 PoseIndex) const override;`
- L155 _public prototype_ `TArrayView<const uint16> GetRBFPoseBlendShapeChannelOutputIndices(uint16 PoseIndex) const override;`
- L156 _public prototype_ `TArrayView<const uint16> GetRBFPoseAnimatedMapOutputIndices(uint16 PoseIndex) const override;`
- L157 _public prototype_ `TArrayView<const float> GetRBFPoseJointOutputValues(uint16 PoseIndex) const override;`
- L158 _public prototype_ `float GetRBFPoseScale(uint16 PoseIndex) const override;`
- L159 _public prototype_ `uint16 GetRBFPoseControlCount() const override;`
- L160 _public prototype_ `FString GetRBFPoseControlName(uint16 PoseControlIndex) const override;`
- L161 _public prototype_ `TArrayView<const uint16> GetRBFPoseInputControlIndices(uint16 PoseIndex) const override;`
- L162 _public prototype_ `TArrayView<const uint16> GetRBFPoseOutputControlIndices(uint16 PoseIndex) const override;`
- L163 _public prototype_ `TArrayView<const float> GetRBFPoseOutputControlWeights(uint16 PoseIndex) const override;`
- L164 _public prototype_ `uint16 GetRBFSolverCount() const override;`
- L165 _public prototype_ `uint16 GetRBFSolverIndexListCount() const override;`
- L166 _public prototype_ `TArrayView<const uint16> GetRBFSolverIndicesForLOD(uint16 LOD) const override;`
- L167 _public prototype_ `FString GetRBFSolverName(uint16 SolverIndex) const override;`
- L168 _public prototype_ `TArrayView<const uint16> GetRBFSolverRawControlIndices(uint16 SolverIndex) const override;`
- L169 _public prototype_ `TArrayView<const uint16> GetRBFSolverPoseIndices(uint16 SolverIndex) const override;`
- L170 _public prototype_ `TArrayView<const float> GetRBFSolverRawControlValues(uint16 SolverIndex) const override;`
- L171 _public prototype_ `ERBFSolverType GetRBFSolverType(uint16 SolverIndex) const override;`
- L172 _public prototype_ `float GetRBFSolverRadius(uint16 SolverIndex) const override;`
- L173 _public prototype_ `EAutomaticRadius GetRBFSolverAutomaticRadius(uint16 SolverIndex) const override;`
- L174 _public prototype_ `float GetRBFSolverWeightThreshold(uint16 SolverIndex) const override;`
- L175 _public prototype_ `ERBFDistanceMethod GetRBFSolverDistanceMethod(uint16 SolverIndex) const override;`
- L176 _public prototype_ `ERBFNormalizeMethod GetRBFSolverNormalizeMethod(uint16 SolverIndex) const override;`
- L177 _public prototype_ `ERBFFunctionType GetRBFSolverFunctionType(uint16 SolverIndex) const override;`
- L178 _public prototype_ `ETwistAxis GetRBFSolverTwistAxis(uint16 SolverIndex) const override;`
- L180 _public prototype_ `uint16 GetTwistCount() const override;` — TwistSwingBehavior
- L181 _public prototype_ `ETwistAxis GetTwistSetupTwistAxis(uint16 TwistIndex) const override;`
- L182 _public prototype_ `TArrayView<const uint16> GetTwistInputControlIndices(uint16 TwistIndex) const override;`
- L183 _public prototype_ `TArrayView<const uint16> GetTwistOutputJointIndices(uint16 TwistIndex) const override;`
- L184 _public prototype_ `TArrayView<const float> GetTwistBlendWeights(uint16 TwistIndex) const override;`
- L185 _public prototype_ `uint16 GetSwingCount() const override;`
- L186 _public prototype_ `ETwistAxis GetSwingSetupTwistAxis(uint16 SwingIndex) const override;`
- L187 _public prototype_ `TArrayView<const uint16> GetSwingInputControlIndices(uint16 SwingIndex) const override;`
- L188 _public prototype_ `TArrayView<const uint16> GetSwingOutputJointIndices(uint16 SwingIndex) const override;`
- L189 _public prototype_ `TArrayView<const float> GetSwingBlendWeights(uint16 SwingIndex) const override;`
- L191 _public prototype_ `uint16 GetMLTypeCount() const override;` — MachineLearnedBehaviorExtReader
- L192 _public prototype_ `uint16 GetMLOperationSetCount(uint16 MLTypeIndex) const override;`
- L193 _public prototype_ `uint16 GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L194 _public prototype_ `EMachineLearnedBehaviorOperationType GetMLOperationType(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L195 _public prototype_ `TArrayView<const uint32> GetMLOperationParameters(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L196 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationSetIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L197 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L198 _public prototype_ `uint16 GetMLOperationIndexListCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L199 _public prototype_ `TArrayView<const uint16> GetMLOperationIndicesForLOD(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 LOD) const override;`
- L200 _public prototype_ `TArrayView<const uint16> GetMLJointsInputIndices() const override;`
- L201 _public prototype_ `TArrayView<const uint16> GetMLJointsOutputIndices() const override;`
- L202 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterKeys() const override;`
- L203 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterValues() const override;`
- L205 _public prototype_ `void Unload(EDNADataLayer ) override;`
- L207 _public prototype_ `const FDNAConfig& GetConfig() const override;`
- L210 _private function_ `dna::Reader* Unwrap() const override`
- L214 _private member_ `TSharedPtr<IDNAReader> DNAReader = nullptr;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API RIGLOGICMODULE_API`
- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkelMeshDNAReader, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkelMeshDNAReader, Log, All);`

### `Plugins/Animation/RigLogic/Source/RigLogicModule/Public/SkelMeshDNAUtils.h` (Public)


#### enum `ELodUpdateOption`  
`enum class ELodUpdateOption : uint8`  
_L19-25_
- reflection: `UENUM()`
- L21 _public enumerator_ `LOD0Only` — LOD0 Only
- L22 _public enumerator_ `LOD0AndLOD1Only` — LOD0 and LOD1 Only
- L23 _public enumerator_ `LOD1AndHigher` — LOD1 and higher
- L24 _public enumerator_ `All` — All LODs

#### class `USkelMeshDNAUtils`  
`class USkelMeshDNAUtils: public UObject`  
_L31-112_
- reflection: `UCLASS(MinimalAPI, transient)`
- inherits: `UObject`
- desc: A utility class for updating SkeletalMesh joints, base mesh, morph targets and skin weights according to DNA data. After the update, the render data is re-chunked.
- L38 _public prototype_ `static FDNAToSkelMeshMap* CreateMapForUpdatingNeutralMesh(IDNAReader* InDNAReader, USkeletalMesh* InSkelMesh);` — Prepare context object that will allow mapping of DNA structures to SkelMesh ones for updating
- L40 _public prototype_ `static FDNAToSkelMeshMap* CreateMapForUpdatingNeutralMesh(USkeletalMesh* InSkelMesh);` — Prepare context object that will allow mapping of DNA structures extracted from DNAAsset to SkelMesh ones for updating
- L44 _public prototype_ `static void UpdateJoints(USkeletalMesh* InSkelMesh, IDNAReader* InDNAReader, FDNAToSkelMeshMap* InDNAToSkelMeshMap);` — Updates the positions, orientation and scale in the joint hierarchy using the data from DNA file
- L48 _public prototype_ `static void UpdateBaseMesh(USkeletalMesh* InSkelMesh, IDNAReader* InDNAReader, FDNAToSkelMeshMap* InDNAToSkelMeshMap, ELodUpdateOption InUpdateOption = ELodUpdateOption::LOD0Only);` — Updates the base mesh vertex positions for all mesh sections of all LODs, using the data from DNA file NOTE: Not calling RebuildRenderData automatically, it needs to be called explicitly after the first update As the topology doesn't change, for subsequent updates it can be ommited to gain performance
- L50 _public prototype_ `static void UpdateMorphTargets(USkeletalMesh* InSkelMesh, IDNAReader* InDNAReader, FDNAToSkelMeshMap* InDNAToSkelMeshMap, ELodUpdateOption InUpdateOption = ELodUpdateOption::LOD0Only);` — Updates the morph targets for all mesh sections of LODs, using the data from DNA file
- L52 _public prototype_ `static void UpdateSkinWeights(USkeletalMesh* InSkelMesh, IDNAReader* InDNAReader, FDNAToSkelMeshMap* InDNAToSkelMeshMap, ELodUpdateOption InUpdateOption = ELodUpdateOption::LOD0Only);` — Updates the skin weights for all LODs using the data from DNA file
- L54 _public prototype_ `static void RebuildRenderData(USkeletalMesh* InSkelMesh);` — Rechunks the mesh after the update
- L56 _public prototype_ `static void RebuildRenderData_VertexPosition(USkeletalMesh* InSkelMesh, bool InRebuildTangents = false);` — Re-initialize vertex positions for rendering after the update, and optionally tangents
- L59 _public prototype_ `static void UpdateJointBehavior(USkeletalMeshComponent* InSkelMeshComponent);` — NOTE: DNAAsset->SetBehaviorReader needs to be called before this
- L63 _public prototype_ `static UDNAAsset* GetMeshDNA(USkeletalMesh* InSkelMesh);` — `UE_DEPRECATED(5.8, "Use GetMeshDNAAsset instead which returns the new UDNA asset type")` — Gets the DNA asset embedded in the mesh
- L66 _public prototype_ `static UDNA* GetMeshDNAAsset(USkeletalMesh* InSkelMesh);` — Gets the DNA asset embedded in the mesh
- L69 _public prototype_ `static TSharedPtr<IDNAReader> GetDNAReader(USkeletalMesh* InSkelMesh);` — Gets DNA Reader either from old version of UDNAAsset or new UDNA, because the reader is widely used so having that in function can be useful
- L76 _public prototype_ `static void SetDNAReader(USkeletalMesh* InSkelMesh, TSharedPtr<IDNAReader> InDNAReader, EDNACopyPolicy CopyPolicy = EDNACopyPolicy::Copy, ERigLogicInitPolicy InitPolicy = ERigLogicInitPolicy::Initialize);` — Sets DNA Reader either from old version of UDNAAsset or new UDNA, because the reader is widely used so having that in function can be useful. Pass ERigLogicInitPolicy::Defer when this call is immediately followed by another operation that rebuilds the runtime context (e.g. RestoreLegacyUEMHCCompatibility).
- L82 _public function_ `inline static FVector ConvertDNAVertexToUE4CoordSystem(FVector InVertexPositionInDNA)` — Converts DNA vertex coordinates to UE4 coordinate system
- L88 _public function_ `inline static FVector ConvertUE4CoordSystemToDNAVertex(FVector InVertexPositionInUE4)` — Converts UE4 coordinate system to DNA vertex coordinates
- L95 _private function_ `inline static void GetLODRange(ELodUpdateOption InUpdateOption, const int32& InLODNum, int32& OutLODStart, int32& OutLODRangeSize)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGLOGICMODULE_API`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAUtils, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAUtils, Log, All);`
