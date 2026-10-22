# Runtime / AnimationCore

- module root: `Source/Runtime/AnimationCore`
- headers: 18; symbols: 530
- symbol kinds: class=5, delegate=4, enum=6, enumerator=19, function=284, macro=5, member=90, namespace=9, prototype=61, struct=32, typedef=9, variable=6
- PrivateIncludePathModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/AnimationCore/Private/AnimationCoreUtil.h` (Private)


#### struct `FComponentBlendHelper`  
`struct FComponentBlendHelper`  
_L11-204_
- L13 _public function_ `void Reset()`
- L24 _public function_ `void AddParent(const FTransform& InTransform, float Weight)`
- L31 _public function_ `void AddTranslation(const FVector& Translation, float Weight)`
- L38 _public function_ `void AddRotation(const FQuat& Rotation, float Weight)`
- L45 _public function_ `void AddScale(const FVector& Scale, float Weight)`
- L52 _public function_ `bool GetBlendedParent(FTransform& OutTransform)`
- L91 _public function_ `bool GetBlendedTranslation(FVector& Output)`
- L117 _public function_ `bool GetBlendedRotation(FQuat& Output)`
- L157 _public function_ `bool GetBlendedScale(FVector& Output)`
- L185 _private member_ `TArray<FTransform> Transforms;` — data member to accumulate blending intermediate result per component
- L186 _private member_ `TArray<FVector> Translations;`
- L187 _private member_ `TArray<FQuat> Rotations;`
- L188 _private member_ `TArray<FVector> Scales;`
- L189 _private member_ `TArray<float> ParentWeights;`
- L190 _private member_ `TArray<float> TranslationWeights;`
- L191 _private member_ `TArray<float> RotationWeights;`
- L192 _private member_ `TArray<float> ScaleWeights;`
- L194 _private function_ `float GetTotalWeight(const TArray<float>& Weights)`

#### struct `FMultiTransformBlendHelper`  
`struct FMultiTransformBlendHelper`  
_L206-392_
- L208 _public function_ `void Reset()`
- L219 _public function_ `void AddParent(const FTransform& InTransform, float Weight)`
- L226 _public function_ `void AddTranslation(const FVector& Translation, float Weight)`
- L233 _public function_ `void AddRotation(const FQuat& Rotation, float Weight)`
- L240 _public function_ `void AddScale(const FVector& Scale, float Weight)`
- L247 _public function_ `bool GetBlendedParent(FTransform& OutTransform)`
- L279 _public function_ `bool GetBlendedTranslation(FVector& Output)`
- L305 _public function_ `bool GetBlendedRotation(FQuat& Output)`
- L345 _public function_ `bool GetBlendedScale(FVector& Output)`
- L373 _private member_ `TArray<FTransform> Transforms;` — data member to accumulate blending intermediate result per component
- L374 _private member_ `TArray<FVector> Translations;`
- L375 _private member_ `TArray<FQuat> Rotations;`
- L376 _private member_ `TArray<FVector> Scales;`
- L377 _private member_ `TArray<float> ParentWeights;`
- L378 _private member_ `TArray<float> TranslationWeights;`
- L379 _private member_ `TArray<float> RotationWeights;`
- L380 _private member_ `TArray<float> ScaleWeights;`
- L382 _private function_ `float GetTotalWeight(const TArray<float>& Weights)`

### `Source/Runtime/AnimationCore/Public/AngularLimit.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace AnimationCore`
- L17 _prototype_ `bool ConstrainAngularRangeUsingEuler(FQuat& InOutQuatRotation, const FQuat& InRefRotation, const FVector& InLimitMinDegrees, const FVector& InLimitMaxDegrees);` (scope `AnimationCore`)

### `Source/Runtime/AnimationCore/Public/AnimationCore.h` (Public)


#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationCore, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationCore, Log, All);`

### `Source/Runtime/AnimationCore/Public/AnimationCoreLibrary.h` (Public)


#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FTransform, FGetGlobalTransform, FName);`
- L22 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FTransform, FGetGlobalTransform, FName);`
- L24 _namespace_ `namespace AnimationCore`
- L36 _prototype_ `FTransform SolveConstraints(const FTransform& CurrentTransform, const FTransform& BaseTransform, const TArray<FTransformConstraint>& Constraints, const FGetGlobalTransform& OnGetGlobalTransform);` (scope `AnimationCore`) — Resolve Constraints based on input constraints data and current transform @param	CurrentTransform		Current transform, based on BaseTransform @param	BaseTransform			Base transform of the current transform, where Constraint transform would be converted @param	Constraints				List of constraints to be used by this transform @param	OnGetGlobalTransform	Delegate to get transform data for constraints @return resolved transform
- L46 _prototype_ `FTransform SolveConstraints(const FTransform& CurrentTransform, const FTransform& CurrentParentTransform, const TArray<FConstraintData>& Constraints);` (scope `AnimationCore`) — Resolve Constraints based on input constraints data and current transform @param	CurrentTransform		Current transform, based on BaseTransform @param	BaseTransform			Base transform of the current transform, where Constraint transform would be converted @param	Constraints				List of constraints - should contains latest transform @return resolved transform
- L61 _prototype_ `FQuat SolveAim(const FTransform& CurrentTransform, const FVector& TargetPosition, const FVector& AimVector, bool bUseUpVector = false, const FVector& UpVector = FVector::UpVector, float AimClampInDegree = 0.f);` (scope `AnimationCore`) — Aim solver This solves new transform that aims at the target based on inputs @param	CurrentTransform	Current Transform @param	TargetPosition		Target to look at @param	AimVector			Aim vector in Current Transform @param	bUseUpVector		Whether or not to use Up vector @param	UpVector			Up Vector in Current Transform if bUseUpVector is true @param	AimClampInDegree	Clamp cone around the AimVector @return  Delta Rotation to turn
- L67 _prototype_ `FQuat QuatFromEuler(const FVector& XYZAnglesInDegrees, EEulerRotationOrder RotationOrderr = EEulerRotationOrder::ZYX, bool bUseUEHandyness = false);` (scope `AnimationCore`) — Converts a euler rotation represented by a vector of rotations in degrees and a rotation order to a quaternion bUseUEHandyness If True will use UE handyness with right handed X and Y angles left handed Z, if False all are left handed
- L73 _prototype_ `FVector EulerFromQuat(const FQuat& Rotation, EEulerRotationOrder RotationOrder = EEulerRotationOrder::ZYX, bool bUseUEHandyness = false);` (scope `AnimationCore`) — Converts a quaternion to a euler rotation represented by a vector of rotations in degrees and a rotation order bUseUEHandyness If True will use UE handyness with right handed X and Y angles left handed Z, if False all are left handed
- L78 _prototype_ `FVector ChangeEulerRotationOrder(const FVector& XYZAnglesInDegrees, EEulerRotationOrder SourceRotationOrder, EEulerRotationOrder TargetRotationOrder, bool bUseUEHandyness = false);` (scope `AnimationCore`) — Converts a euler rotation from one rotation order to another

### `Source/Runtime/AnimationCore/Public/AnimationDataSource.h` (Public)


#### class `UAnimationDataSourceRegistry`  
`class UAnimationDataSourceRegistry : public UObject`  
_L20-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L34 _public prototype_ `bool RegisterDataSource(const FName& InName, UObject* InDataSource);` — Registers a new data source under a given name. Returns false in case the data source has already been registered. @param InName         The name to register the data source under @param InDataSource   The data source to register @return true if succeeded
- L43 _public prototype_ `bool UnregisterDataSource(const FName& InName);` — Unregisters / removes an existing data source under a given name. Returns false in case the data source has already been unregistered. @param InName The name of the data source to remove @return true if succeeded
- L51 _public prototype_ `bool ContainsSource(const FName& InName) const;` — Returns true if this registry contains a source with the given name @param InName The name of the data source to look up. @return true if a source with the given name exists
- L60 _public prototype_ `UObject* RequestSource(const FName& InName, UClass* InExpectedClass) const;` — Returns a given data source and cast it to the expected class. @param InName The name of the data source to look up. @param InExpectedClass The class expected from the data source @return The requested data source
- L69 _public function_ `template<class T> T* RequestSource(const FName& InName) const` — Returns a given data source and cast it to the expected class. @param InName The name of the data source to look up. @return The requested data source
- L82 _private member_ `TMap<FName, TWeakObjectPtr<UObject>> DataSources;` — `UPROPERTY(transient)`
- L85 _private prototype_ `void ClearInvalidDataSource();` — Clear Invalid Data Sources that are GC-ed

### `Source/Runtime/AnimationCore/Public/BoneIndices.h` (Public)


#### struct `FBoneIndexBase`  
`struct FBoneIndexBase`  
_L13-32_
- L15 _public function_ `FBoneIndexBase() : BoneIndex(INDEX_NONE)`
- L17 _public function_ `inline int32 GetInt() const`
- L18 _public function_ `inline FBoneIndexType GetBoneIndex() const`
- L20 _public function_ `inline bool IsRootBone() const`
- L22 _public function_ `inline bool IsValid() const`
- L24 _public function_ `inline explicit operator int32() const`
- L26 _public function_ `inline explicit operator bool() const`
- L31 _protected member_ `int32 BoneIndex;`

#### struct `FCompactPoseBoneIndex`  
`struct FCompactPoseBoneIndex : public FBoneIndexBase`  
_L66-73_
- inherits: `FBoneIndexBase`
- desc: This represents a compact pose bone index. A compact pose is held by a bone container and can have a different ordering than either the skeleton or skeletal mesh.
- L69 _public prototype_ `FCompactPoseBoneIndex() = default;`
- L70 _public function_ `explicit FCompactPoseBoneIndex(int32 InBoneIndex)`
- L71 _public function_ `explicit FCompactPoseBoneIndex(FBoneIndexType InBoneIndex)` — Handle 16bit -> 32bit

#### struct `FMeshPoseBoneIndex`  
`struct FMeshPoseBoneIndex : public FBoneIndexBase`  
_L76-83_
- inherits: `FBoneIndexBase`
- desc: This represents a skeletal mesh bone index which may differ from the skeleton bone index it corresponds to.
- L79 _public prototype_ `FMeshPoseBoneIndex() = default;`
- L80 _public function_ `explicit FMeshPoseBoneIndex(int32 InBoneIndex)`
- L81 _public function_ `explicit FMeshPoseBoneIndex(FBoneIndexType InBoneIndex)` — Handle 16bit -> 32bit

#### struct `FSkeletonPoseBoneIndex`  
`struct FSkeletonPoseBoneIndex : public FBoneIndexBase`  
_L86-93_
- inherits: `FBoneIndexBase`
- desc: This represents a skeleton bone index which may differ from the skeletal mesh bone index it corresponds to.
- L89 _public prototype_ `FSkeletonPoseBoneIndex() = default;`
- L90 _public function_ `explicit FSkeletonPoseBoneIndex(int32 InBoneIndex)`
- L91 _public function_ `explicit FSkeletonPoseBoneIndex(FBoneIndexType InBoneIndex)` — Handle 16bit -> 32bit

#### struct `TCompactPoseBoneIndexMapKeyFuncs`  
`template <typename ValueType> struct TCompactPoseBoneIndexMapKeyFuncs : public TDefaultMapKeyFuncs<const FCompactPoseBoneIndex, ValueType, false>`  
_L96-101_
- inherits: `TDefaultMapKeyFuncs<constFCompactPoseBoneIndex,ValueType,false>`
- L98 _public function_ `static inline FCompactPoseBoneIndex GetSetKey(TPair<FCompactPoseBoneIndex, ValueType> const& Element)`
- L99 _public function_ `static inline uint32 GetKeyHash(FCompactPoseBoneIndex const& Key)`
- L100 _public function_ `static inline bool Matches(FCompactPoseBoneIndex const& A, FCompactPoseBoneIndex const& B)`

#### Free symbols / members of external scopes

- L7 _typedef_ `typedef uint16 FBoneIndexType;`
- L10 _macro_ `#define INVALID_BONE_INDEX FBoneIndexType(INDEX_NONE)` — Important: only use this define when comparing FBoneIndexType (16 bit), it should not be used to compare 32 bit bone indicies stored in FBoneIndexBase
- L28 _function_ `friend inline uint32 GetTypeHash(const FBoneIndexBase& Index)`
- L34 _function_ `inline int32 GetIntFromComp(const int32 InComp)`
- L39 _function_ `inline int32 GetIntFromComp(const FBoneIndexBase& InComp)`
- L44 _macro_ `#define UE_BONE_INDEX_COMPARE_OPERATORS(LhsType, RhsType) \`
- L52 _macro_ `#define UE_BONE_INDEX_COMPARE_OPERATORS_INVERTED UE_BONE_INDEX_COMPARE_OPERATORS(const int32, const Type&)`
- L54 _macro_ `#define UE_BONE_INDEX_COMPARE_OPERATORS_INVERTED`
- L57 _macro_ `#define UE_BONE_INDEX_OPERATORS(Type) \`

### `Source/Runtime/AnimationCore/Public/BoneWeights.h` (Public)


#### class `UE::AnimationCore::FBoneWeight`  
`class FBoneWeight`  
_L47-208_
- L54 _public function_ `bool operator==(const FBoneWeight& InBoneWeight) const` — Returns true if this object's bone weight values are equal to the other container's values. @note Only equality comparison are supported. Relational comparisons are meaningless.
- L63 _public function_ `bool operator!=(const FBoneWeight& InBoneWeight) const` — Returns true if this object's bone weight values are not equal to the other container's values. @note Only equality comparison are supported. Relational comparisons are meaningless.
- L71 _public function_ `static constexpr uint16 GetMaxRawWeight()` — The maximum raw weight value for a bone influence.
- L77 _public function_ `static bool DescSortByWeightPredicate(const FBoneWeight& A, const FBoneWeight& B)` — A standard predicate we use for sorting by weight, in a descending order of weights
- L83 _public prototype_ `FBoneWeight() = default;` — Default constructor. NOTE: The values are uninitialized.
- L89 _public function_ `explicit FBoneWeight(FBoneIndexType InBoneIndex, uint8 InWeight) : BoneIndex(InBoneIndex)` — A constructor for old-style bone weights where the weight was stored as an unsigned eight bit integer.
- L99 _public function_ `explicit FBoneWeight(FBoneIndexType InBoneIndex, uint16 InRawWeight) : BoneIndex(InBoneIndex), RawWeight(InRawWeight)` — A constructor for bone weights where the weight is stored as an unsigned sixteen bit integer. This is the natural storage format for this container.
- L108 _public function_ `explicit FBoneWeight(FBoneIndexType InBoneIndex, float InWeight) : BoneIndex(InBoneIndex)` — A constructor for bone weights which converts the weight from a float value in the [0-1] range. Values outside of that range are clamped to the range.
- L117 _public function_ `void SetBoneIndex(FBoneIndexType InBoneIndex)` — Set the bone stored index.
- L125 _public function_ `FBoneIndexType GetBoneIndex() const` — Returns the bone stored index.
- L134 _public function_ `void SetWeight(float InWeight)` — Set stored weight as a float. Values outside the [0-1] range are clamped to that range. Undefined float values will result in an undefined weight.
- L143 _public function_ `float GetWeight() const` — Returns the stored weight value as a float in the [0-1] range.
- L151 _public function_ `void SetRawWeight(const uint16 InRawWeight)` — Set the stored weight in the raw format. This avoids any floating point conversion.
- L160 _public function_ `uint16 GetRawWeight() const` — Returns the stored weight in the container's raw format, avoiding floating point conversion.
- L165 _public function_ `void Serialize(FArchive& InArchive)`
- L172 _public function_ `uint32 GetTypeHash() const` — Returns a hash value from the bone weight values
- L180 _public function_ `FString ToString() const` — A helper function to return a human-readable version of the bone weight.
- L189 _public function_ `int32 ToInt32() const` — Returns the contents of this object as an int32.
- L197 _public function_ `static FBoneWeight FromInt32(int32 InBoneWeight)` — Converts an int32 to an FBoneWeight object and returns it.
- L206 _private member_ `FBoneIndexType BoneIndex;`
- L207 _private member_ `uint16 RawWeight;`

#### enum `UE::AnimationCore::EBoneWeightNormalizeType`  
`enum class EBoneWeightNormalizeType`  
_L215-225_
- desc: Specifies the method for which the bone weights are normalized after the bone weight list is modified.
- L218 _public enumerator_ `None` — No normalization is performed. The sum of the weight values can exceed 1.0
- L221 _public enumerator_ `AboveOne` — Normalization is only performed if the sum of the weights exceeds 1.0
- L224 _public enumerator_ `Always` — Normalization is always performed such that the sum of the weights is always equal to 1.0

#### class `UE::AnimationCore::FBoneWeightsSettings`  
`class FBoneWeightsSettings`  
_L228-335_
- L231 _public prototype_ `FBoneWeightsSettings() = default;`
- L234 _public function_ `FBoneWeightsSettings& SetNormalizeType(EBoneWeightNormalizeType InNormalizeType)` — Set the normalization type when manipulating the weight values in FBoneWeights
- L241 _public function_ `EBoneWeightNormalizeType GetNormalizeType() const` — Returns the current normalization type for these settings
- L246 _public function_ `FBoneWeightsSettings& SetMaxWeightCount(int32 InMaxWeightCount)` — Sets the maximum number of weights that can be applied to a single FBoneWeights object. When weights are added, the smallest weights, past this limit, are dropped.
- L253 _public function_ `int32 GetMaxWeightCount() const` — Returns the maximum number of weights for these settings
- L260 _public function_ `FBoneWeightsSettings& SetWeightThreshold(float InWeightThreshold)` — Sets the minimum influence allowed. Any bone weight value below this threshold value is discarded. The threshold value is clamped to the half-closed interval (0, 1] since weight values of zero indicate no influence at all and are ignored completely. By default, all non-zero weights are allowed.
- L269 _public function_ `float GetWeightThreshold() const` — Returns the weight threshold as a float value between (0, 1].
- L277 _public function_ `uint16 GetRawWeightThreshold() const` — Returns the raw weight threshold. This is the value used internally for weight computation.
- L284 _public function_ `void SetDefaultBoneIndex(FBoneIndexType InBoneIndex)` — Set the default bone index to use if no weights were set. This can be used to ensure that there's always a valid weight applied to a skinned vertex.
- L293 _public function_ `FBoneIndexType GetDefaultBoneIndex() const` — Returns the current default bone index to set if no weights were set. If no default bone index has been set, then this value is undefined. Call HasDefaultBoneIndex to check
- L300 _public function_ `void ClearDefaultBoneIndex()` — Clears the default bone index. This allows bone weights arrays to be empty if no weights are set.
- L307 _public function_ `bool HasDefaultBoneIndex() const` — Returns \c true if a default bone index should be applied in the absence of other weights.
- L316 _public function_ `void SetBlendZeroInfluence(bool bInBlendZeroInfluence)` — Set the way we treat the bones with zero influence during the blend. If true, we assume all bones with no influence have a zero weight (default) and participate in the blend calculation. If false, we ignore the bone during the blend.
- L323 _public function_ `bool GetBlendZeroInfluence() const` — Return true if bones with no influence are considered to have a zero weight during the blend calculation.
- L329 _private member_ `EBoneWeightNormalizeType NormalizeType = EBoneWeightNormalizeType::Always;`
- L330 _private member_ `int32 MaxWeightCount = MaxInlineBoneWeightCount;`
- L331 _private member_ `uint16 WeightThreshold = 1;`
- L332 _private member_ `FBoneIndexType DefaultBoneIndex = static_cast<FBoneIndexType>(0);`
- L333 _private member_ `bool bHasDefaultBoneIndex = false;`
- L334 _private member_ `bool bBlendZeroInfluence = true;`

#### struct `UE::AnimationCore::FBoneWeightNullAdapter`  
`struct FBoneWeightNullAdapter`  
_L339-383_
- desc: A null adapter for a bone weight container to use with TBoneWeights. Use as a template to create adapters for other types of containers.
- L342 _public typedef_ `using ContainerType = Empty;`
- L347 _public function_ `static void SetNum(ContainerType& InContainer, int32 InNum)` — Set the number of elements to reserve in the container. The elements can be left in an uninitialized state. The TBoneWeights algorithms will ensure that all elements will be properly defined at the end of an operation.
- L351 _public function_ `static int32 Num(const ContainerType& InContainer)`
- L356 _public function_ `static FBoneWeight Get(const ContainerType& InContainer, int32 InIndex)`
- L361 _public function_ `static void Set(ContainerType& InContainer, int32 InIndex, FBoneWeight InBoneWeight)`
- L365 _public function_ `static void Add(ContainerType& InContainer, FBoneWeight InBoneWeight)`
- L369 _public function_ `static void Remove(ContainerType& InContainer, int32 InIndex)`
- L374 _public function_ `template<typename Predicate> static void Sort(ContainerType& InContainer, Predicate InPredicate)`
- L379 _public function_ `template<typename Predicate> static int32 IndexOf(const ContainerType& InContainer, Predicate InPredicate)`

#### struct `UE::AnimationCore::FBoneWeightNullAdapter::Empty`  
`struct Empty`  
_L341-341_

#### class `UE::AnimationCore::TBoneWeights`  
`template<typename ContainerAdapter> class TBoneWeights`  
_L389-520_
- desc: A templated collection of bone weights algorithms. Requires an adapter to work with a dynamically resizable container.
- L392 _public typedef_ `using ContainerType = typename ContainerAdapter::ContainerType;`
- L394 _public function_ `TBoneWeights(ContainerType& InContainer) : Container(InContainer)`
- L400 _public prototype_ `SetBoneWeights( const TBoneWeights<OtherContainerAdapter> &InBoneWeights, const FBoneWeightsSettings& InSettings = {});`
- L406 _public prototype_ `SetBoneWeights( TArrayView<const FBoneWeight> BoneWeights, const FBoneWeightsSettings& InSettings = {});`
- L412 _public prototype_ `SetBoneWeights( const FBoneIndexType* InBones, const float* InInfluences, int32 NumEntries, const FBoneWeightsSettings& InSettings = {} );`
- L421 _public prototype_ `SetBoneWeights( const FBoneIndexType InBones[MaxInlineBoneWeightCount], const uint16 InInfluences[MaxInlineBoneWeightCount], const FBoneWeightsSettings& InSettings = {});`
- L428 _public prototype_ `AddBoneWeight( FBoneWeight InBoneWeight, const FBoneWeightsSettings& InSettings = {} );`
- L435 _public prototype_ `RemoveBoneWeight( FBoneIndexType InBoneIndex, const FBoneWeightsSettings& InSettings = {} );`
- L442 _public prototype_ `Renormalize( const FBoneWeightsSettings& InSettings = {} );`
- L453 _public prototype_ `Blend( const TBoneWeights<ContainerTypeA>& InBoneWeightsA, const TBoneWeights<ContainerTypeB>& InBoneWeightsB, float InBias, const FBoneWeightsSettings& InSettings = {});`
- L459 _public function_ `int32 Num() const`
- L464 _public function_ `FBoneWeight Get(int32 Index) const`
- L469 _public function_ `FBoneWeight operator[](int32 Index) const`
- L474 _public function_ `int32 FindWeightIndexByBone( FBoneIndexType InBoneIndex ) const`
- L481 _public function_ `int32 GetTypeHash() const`
- L491 _public function_ `FString ToString() const`
- L508 _private prototype_ `inline void SetBoneWeightsInternal( TArrayView<FBoneWeight> BoneWeights, const FBoneWeightsSettings& InSettings = {});`
- L512 _private prototype_ `inline void SortWeights();`
- L513 _private prototype_ `inline bool CullWeights(const FBoneWeightsSettings& InSettings);`
- L514 _private prototype_ `inline void NormalizeWeights(EBoneWeightNormalizeType InNormalizeType);`
- L516 _private prototype_ `inline bool Verify() const;`
- L519 _private member_ `ContainerType &Container;` — The externally owned container we're operating on.
- L755 _function_ `TBoneWeights<ContainerAdapter>::SetBoneWeights( const TBoneWeights<OtherContainerAdapter>& InBoneWeights, const FBoneWeightsSettings& InSettings )`
- L776 _function_ `TBoneWeights<ContainerAdapter>::SetBoneWeights( TArrayView<const FBoneWeight> InBoneWeights, const FBoneWeightsSettings& InSettings )`
- L798 _function_ `TBoneWeights<ContainerAdapter>::SetBoneWeights( const FBoneIndexType* InBones, const float* InInfluences, int32 NumEntries, const FBoneWeightsSettings& InSettings )`
- L823 _function_ `TBoneWeights<ContainerAdapter>::SetBoneWeights( const FBoneIndexType InBones[MaxInlineBoneWeightCount], const uint16 InInfluences[MaxInlineBoneWeightCount], const FBoneWeightsSettings& InSettings )`
- L864 _function_ `template<typename ContainerAdapter> void TBoneWeights<ContainerAdapter>::SetBoneWeightsInternal( TArrayView<FBoneWeight> BoneWeights, const FBoneWeightsSettings& InSettings )`
- L891 _function_ `TBoneWeights<ContainerAdapter>::AddBoneWeight( FBoneWeight InBoneWeight, const FBoneWeightsSettings& InSettings )`
- L977 _function_ `TBoneWeights<ContainerAdapter>::RemoveBoneWeight( FBoneIndexType InBoneIndex, const FBoneWeightsSettings& InSettings )`
- L1007 _function_ `TBoneWeights<ContainerAdapter>::Renormalize( const FBoneWeightsSettings& InSettings )`
- L1024 _function_ `TBoneWeights<ContainerAdapter>::Blend( const TBoneWeights<ContainerAdapterA>& InBoneWeightsA, const TBoneWeights<ContainerAdapterB>& InBoneWeightsB, const float InBias, const FBoneWeightsSettings& InSettings )`
- L1138 _function_ `template<typename ContainerAdapter> void TBoneWeights<ContainerAdapter>::SortWeights()`
- L1145 _function_ `template<typename ContainerAdapter> bool TBoneWeights<ContainerAdapter>::CullWeights( const FBoneWeightsSettings& InSettings )`
- L1173 _function_ `template<typename ContainerAdapter> void TBoneWeights<ContainerAdapter>::NormalizeWeights( EBoneWeightNormalizeType InNormalizeType )`

#### class `UE::AnimationCore::FBoneWeights`  
`class FBoneWeights`  
_L524-748_
- desc: A simple container for per-vertex influence of bones and their weights.
- L526 _private typedef_ `using BoneWeightsTempAllocatorT = TInlineAllocator<MaxInlineBoneWeightCount>;`
- L527 _private typedef_ `using BoneWeightArrayT = TArray<FBoneWeight, BoneWeightsTempAllocatorT>;`
- L576 _private typedef_ `using FArrayWrapper = TBoneWeights<TArrayAdapter<BoneWeightArrayT>>;`
- L579 _public prototype_ `FBoneWeights() = default;`
- L586 _public function_ `bool operator==(const FBoneWeights& InBoneWeight) const` — Returns true if all of this container's values and count are equal to the other container's values and count. @note Only equality comparison are supported. Relational comparisons are meaningless.
- L595 _public function_ `bool operator!=(const FBoneWeights& InBoneWeight) const` — Returns true if this container's values are equal to the other container's values. @note Only equality comparison are supported. Relational comparisons are meaningless.
- L607 _public prototype_ `inline bool SetBoneWeight( FBoneWeight InBoneWeight, const FBoneWeightsSettings& InSettings = {});` — Set a new bone weight. If an existing weight exists with the same bone index, it's weight value is replaced with the weight value of the given entry. Otherwise a new index is added. In both cases the new entry is subject to the given settings, which may influence what the entry's final weight value is and whether it gets thrown away for not passing the threshold value. If the weight was successfully incorporated, then this function returns true. Otherwise it returns false.
- L611 _public function_ `bool SetBoneWeight( FBoneIndexType InBone, float InWeight, const FBoneWeightsSettings& InSettings = {})`
- L622 _public prototype_ `inline bool RemoveBoneWeight( FBoneIndexType InBone, const FBoneWeightsSettings& InSettings = {});` — Removes a specific bone from the list of weights, re-normalizing and pruning bones, if needed.
- L629 _public prototype_ `inline void Renormalize(const FBoneWeightsSettings& InSettings = {});` — Force normalization of weights. This is useful if a set of operations were performed with no normalization, for efficiency, and normalization is needed post-operation.
- L632 _public prototype_ `static inline FBoneWeights Create( const FBoneIndexType InBones[MaxInlineBoneWeightCount], const uint16 InWeights[MaxInlineBoneWeightCount], const FBoneWeightsSettings& InSettings = {});` — A helper to create a FBoneWeights container from FSoftSkinVertex data structure.
- L640 _public prototype_ `static inline FBoneWeights Create( const FBoneIndexType* InBones, const float* InWeights, int32 NumEntries, const FBoneWeightsSettings& InSettings = {});` — A helper to create a FBoneWeights container from separated bone index and weight arrays. The size of the two arrays *must* be the same -- otherwise the behavior is undefined.
- L647 _public prototype_ `static inline FBoneWeights Create( TArrayView<const FBoneWeight> BoneWeights, const FBoneWeightsSettings& InSettings = {});` — A helper to create FBoneWeights container from a TArray of FBoneWeight objects.
- L653 _public function_ `template<typename OtherContainerAdapter> static FBoneWeights Create( TBoneWeights<OtherContainerAdapter> InBoneWeights, const FBoneWeightsSettings& InSettings = {})` — A helper to create FBoneWeights container from a TBoneWeights derivative object
- L667 _public prototype_ `static inline FBoneWeights Blend( const FBoneWeights& InA, const FBoneWeights& InB, float InBias, const FBoneWeightsSettings& InSettings = {});` — Blend two bone weights together, making sure to add in every influence from both, using the given settings. The bias value should lie on the [0,1] interval. Values outside that range may give unwanted results.
- L676 _public prototype_ `static inline FBoneWeights Blend( const FBoneWeights& InA, const FBoneWeights& InB, const FBoneWeights& InC, float InBaryX, float InBaryY, float InBaryZ, const FBoneWeightsSettings& InSettings = {});` — Blend three bone weights via barycentric coordinates using the given settings. Considers the influence from all of the bones. Coordinates should sum to one.
- L686 _public typedef_ `using RangedForConstIteratorType = BoneWeightArrayT::RangedForConstIteratorType;` — Ranged-based for loop compatibility -- but only the const version.
- L688 _public function_ `RangedForConstIteratorType begin() const`
- L689 _public function_ `RangedForConstIteratorType end() const`
- L694 _public function_ `int32 Num() const` — Return the number of bone weights in this container. @return The number of bone weights.
- L701 _public function_ `const FBoneWeight& operator[](int32 Index) const` — Return the weight at index Index. Using an index value less than zero -- or equal to or greater than the result of Num() -- is an undefined operation. @param Index The index of the desired bone weight value. @return The bone weight value for that index, or undefined if outside the valid range.
- L704 _public function_ `TArrayView<const FBoneWeight> ToArrayView() const` — Returns the FBoneWeight list as an array view
- L714 _public function_ `int32 FindWeightIndexByBone(FBoneIndexType InBoneIndex) const` — Find the bone weight corresponding to the given bone index. If a bone weight with this bone index does not exist it, a value of INDEX_NONE is returned.
- L720 _public function_ `void Serialize(FArchive& InArchive)`
- L725 _public function_ `int32 GetTypeHash() const`
- L735 _public function_ `FString ToString() const`
- L747 _private member_ `BoneWeightArrayT BoneWeights;` — List of bone weights, in order of descending weight.
- L1303 _function_ `bool FBoneWeights::SetBoneWeight( FBoneWeight InBoneWeight, const FBoneWeightsSettings& InSettings )`
- L1313 _function_ `bool FBoneWeights::RemoveBoneWeight( FBoneIndexType InBoneIndex, const FBoneWeightsSettings& InSettings )`
- L1323 _function_ `void FBoneWeights::Renormalize(const FBoneWeightsSettings& InSettings )`
- L1330 _function_ `FBoneWeights FBoneWeights::Create( const FBoneIndexType InBones[MaxInlineBoneWeightCount], const uint16 InInfluences[MaxInlineBoneWeightCount], const FBoneWeightsSettings& InSettings )`
- L1343 _function_ `FBoneWeights FBoneWeights::Create( const FBoneIndexType* InBones, const float* InInfluences, int32 NumEntries, const FBoneWeightsSettings& InSettings )`
- L1357 _function_ `FBoneWeights FBoneWeights::Create( TArrayView<const FBoneWeight> InBoneWeights, const FBoneWeightsSettings& InSettings )`
- L1368 _function_ `FBoneWeights FBoneWeights::Blend( const FBoneWeights& InA, const FBoneWeights& InB, float InBias, const FBoneWeightsSettings& InSettings )`
- L1383 _function_ `FBoneWeights FBoneWeights::Blend( const FBoneWeights& InA, const FBoneWeights& InB, const FBoneWeights& InC, float InBaryX, float InBaryY, float InBaryZ, const FBoneWeightsSettings& InSettings)`

#### struct `UE::AnimationCore::FBoneWeights::TArrayAdapter`  
`template<typename T> struct TArrayAdapter`  
_L530-575_
- L532 _public typedef_ `using ContainerType = T;`
- L534 _public function_ `static void SetNum(ContainerType& InContainer, int32 InNum)`
- L539 _public function_ `static int32 Num(const ContainerType& InContainer)`
- L544 _public function_ `static FBoneWeight Get(const ContainerType& InContainer, int32 InIndex)`
- L549 _public function_ `static void Set(ContainerType& InContainer, int32 InIndex, FBoneWeight InBoneWeight)`
- L554 _public function_ `static void Add(ContainerType& InContainer, FBoneWeight InBoneWeight)`
- L559 _public function_ `static void Remove(ContainerType& InContainer, int32 InIndex)`
- L565 _public function_ `template<typename Predicate> static void Sort(ContainerType& InContainer, Predicate InPredicate)`
- L571 _public function_ `template<typename Predicate> static int32 IndexOf(const ContainerType& InContainer, Predicate InPredicate)`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L27 _namespace_ `namespace AnimationCore` (scope `UE`)
- L32 _variable_ `static constexpr int32 MaxInlineBoneWeightCount = MAX_TOTAL_INFLUENCES;` (scope `UE::AnimationCore`) — The maximum number of inline bone weights.
- L35 _variable_ `static constexpr uint16 MaxRawBoneWeight = std::numeric_limits<uint16>::max();` (scope `UE::AnimationCore`) — The maximum raw weight value
- L38 _variable_ `static constexpr float MaxRawBoneWeightFloat = static_cast<float>(std::numeric_limits<uint16>::max());` (scope `UE::AnimationCore`) — The maximum raw weight value as a float value
- L41 _variable_ `static constexpr float InvMaxRawBoneWeightFloat = 1.0f / MaxRawBoneWeightFloat;` (scope `UE::AnimationCore`) — The inverse of the maximum raw weight value as a float value. Used for scaling.
- L45 _variable_ `static constexpr float BoneWeightThreshold = InvMaxRawBoneWeightFloat;` (scope `UE::AnimationCore`) — The threshold value at or above which a 0-1 normalized bone weight value will be stored as a non-zero value after scaling and quantizing to a 16-bit integer
- L478 _function_ `return ContainerAdapter::IndexOf(Container, [InBoneIndex](const FBoneWeight& BW) { return InBoneIndex == BW.GetBoneIndex(); });` (scope `UE::AnimationCore::TBoneWeights::FindWeightIndexByBone`)
- L717 _function_ `[InBoneIndex](const FBoneWeight& BW)` (scope `UE::AnimationCore::FBoneWeights::FindWeightIndexByBone`)
- L738 _function_ `Result.Append(FString::JoinBy(BoneWeights, TEXT(", "), [](const FBoneWeight& V) { return V.ToString(); })` (scope `UE::AnimationCore::FBoneWeights::ToString`)
- L1055 _function_ `auto CreateIndirectIndex = [](const auto &InBoneWeights, TArrayView<int32> InIndexIndirect)` (scope `UE::AnimationCore::TBoneWeights::Blend`) — To simplify lookup and iteration over the two bone weight arrays, we sort by bone index value, but indirectly, since we can't sort them directly, as that would violate the sorted-by-descending-weight contract. Instead we create an indirection array on the stack and use that to iterate
- L1060 _function_ `InIndexIndirect.Sort([InBoneWeights](int32 A, int32 B) { return InBoneWeights[A].GetBoneIndex() < InBoneWeights[B].GetBoneIndex(); });` (scope `UE::AnimationCore::TBoneWeights::Blend::__anon97d845440402`)
- L1080 _function_ `` (scope `UE::AnimationCore::TBoneWeights::Blend`)
- L1256 _function_ `template<typename ContainerAdapter> bool UE::AnimationCore::TBoneWeights<ContainerAdapter>::Verify() const` (scope `UE::AnimationCore::UE::AnimationCore::TBoneWeights`)
- L1298 _function_ `static auto WeightSortPredicate = [](const FBoneWeight& A, const FBoneWeight& B)` (scope `UE::AnimationCore`) — FBoneWeights implementations
- L1298 _variable_ `static auto WeightSortPredicate = [](const FBoneWeight& A, const FBoneWeight& B) { return A.GetRawWeight() > B.GetRawWeight(); };` (scope `UE::AnimationCore`) — FBoneWeights implementations
- L1421 _function_ `static inline uint32 GetTypeHash( const UE::AnimationCore::FBoneWeight& InBoneWeight )` — A hashing function to allow the FBoneWeight class to be used with hashing containers (e.g. TSet or TMap).
- L1428 _function_ `static inline FArchive& operator<<( FArchive& InArchive, UE::AnimationCore::FBoneWeight& InOutBoneWeight )`
- L1437 _function_ `static inline uint32 GetTypeHash(const UE::AnimationCore::FBoneWeights& InBoneWeights)`
- L1442 _function_ `static inline FArchive& operator<<( FArchive& InArchive, UE::AnimationCore::FBoneWeights& InOutBoneWeights)`

### `Source/Runtime/AnimationCore/Public/CCDIK.h` (Public)


#### struct `FCCDIKChainLink`  
`struct FCCDIKChainLink`  
_L17-50_
- reflection: `USTRUCT()`
- desc: Transient structure for CCDIK node evaluation
- L23 _public member_ `FTransform Transform;` — Transform of bone in component space.
- L26 _public member_ `FTransform LocalTransform;` — Transform of bone in local space. This is mutable as their component space changes or parents
- L29 _public member_ `int32 TransformIndex;` — Transform Index that this control will output
- L33 _public member_ `TArray<int32> ChildZeroLengthTransformIndices;` — Child bones which are overlapping this bone. They have a zero length distance, so they will inherit this bone's transformation.
- L35 _public member_ `double CurrentAngleDelta;`
- L37 _public function_ `FCCDIKChainLink() : TransformIndex(INDEX_NONE) , CurrentAngleDelta(0.0)`
- L43 _public function_ `FCCDIKChainLink(const FTransform& InTransform, const FTransform& InLocalTransform, const int32& InTransformIndex) : Transform(InTransform) , LocalTransform(InLocalTransform) , TransformIndex(InTransformIndex) , CurrentAngleDelta(0.0)`

#### Free symbols / members of external scopes

- L52 _namespace_ `namespace AnimationCore`
- L54 _prototype_ `bool SolveCCDIK(TArray<FCCDIKChainLink>& InOutChain, const FVector& TargetPosition, float Precision, int32 MaxIteration, bool bStartFromTail, bool bEnableRotationLimit, const TArray<float>& RotationLimitPerJoints);` (scope `AnimationCore`)

### `Source/Runtime/AnimationCore/Public/CommonAnimTypes.h` (Public)


#### struct `FAxis`  
`struct FAxis`  
_L13-60_
- reflection: `USTRUCT()`
- desc: Axis to represent direction
- L18 _public member_ `FVector Axis;` — `UPROPERTY(EditAnywhere, Category = "FAxis")`
- L21 _public member_ `bool bInLocalSpace;` — `UPROPERTY(EditAnywhere, Category = "FAxis")`
- L23 _public function_ `FAxis(const FVector& InAxis = FVector::ForwardVector) : bInLocalSpace(true)`
- L30 _public function_ `FVector GetTransformedAxis(const FTransform& ComponentSpaceTransform) const` — return transformed axis based on ComponentSpaceTransform
- L42 _public function_ `void Initialize()` — Initialize the set up
- L48 _public function_ `bool IsValid() const` — return true if Valid data

#### Free symbols / members of external scopes

- L53 _function_ `friend FArchive & operator<<(FArchive & Ar, FAxis & D)`

### `Source/Runtime/AnimationCore/Public/Constraint.h` (Public)


#### struct `FFilterOptionPerAxis`  
`struct FFilterOptionPerAxis`  
_L42-132_
- reflection: `USTRUCT(BlueprintType)`
- desc: Filter Option Per Axis This is used to filter per axis for constraint options
- L47 _public member_ `bool bX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axis Filter")`
- L50 _public member_ `bool bY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axis Filter")`
- L53 _public member_ `bool bZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axis Filter")`
- L55 _public function_ `FFilterOptionPerAxis() : bX(true) , bY(true) , bZ(true)`
- L61 _public function_ `FFilterOptionPerAxis(bool X, bool Y, bool Z) : bX(X) , bY(Y) , bZ(Z)`
- L67 _public function_ `void FilterVector(FVector& Input, const FVector& ResetValue = FVector::ZeroVector) const`
- L85 _public function_ `void FilterQuat(FQuat& Input, const FQuat& ResetValue = FQuat::Identity) const`
- L94 _public function_ `void FilterRotator(FRotator& Input, const FRotator& ResetValue = FRotator::ZeroRotator) const`
- L121 _public function_ `bool IsValid() const`
- L127 _public function_ `bool HasNoEffect() const`

#### struct `FTransformFilter`  
`struct FTransformFilter`  
_L136-178_
- reflection: `USTRUCT(BlueprintType)`
- desc: A filter for a whole transform
- L141 _public member_ `FFilterOptionPerAxis TranslationFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axis Filter")`
- L144 _public member_ `FFilterOptionPerAxis RotationFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axis Filter")`
- L147 _public member_ `FFilterOptionPerAxis ScaleFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axis Filter")`
- L149 _public function_ `void FilterTransform(FTransform& Input) const`
- L164 _public function_ `void FilterTransform(FEulerTransform& Input) const`

#### struct `FConstraintDescription`  
`struct FConstraintDescription`  
_L182-228_
- reflection: `USTRUCT(BlueprintType)`
- desc: A description of how to apply a simple transform constraint
- L187 _public member_ `bool bTranslation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constraint")`
- L190 _public member_ `bool bRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constraint")`
- L193 _public member_ `bool bScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constraint")`
- L197 _public member_ `bool bParent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constraint")` — this does composed transform - where as individual will accumulate per component
- L200 _public member_ `FFilterOptionPerAxis TranslationAxes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constraint")`
- L203 _public member_ `FFilterOptionPerAxis RotationAxes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constraint")`
- L206 _public member_ `FFilterOptionPerAxis ScaleAxes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constraint")`
- L208 _public function_ `FConstraintDescription() : bTranslation(true) , bRotation(true) , bScale(false) , bParent(false)`

#### struct `FConstraintOffset`  
`struct FConstraintOffset`  
_L237-282_
- reflection: `USTRUCT()`
- desc: This is the offset for constraint Saves individual component (translation, rotation, scale or parent) Used by Constraint for saving the offset, and recovering the offset
- L242 _public member_ `FVector Translation;` — `UPROPERTY()`
- L245 _public member_ `FQuat Rotation;` — `UPROPERTY()`
- L248 _public member_ `FVector Scale;` — `UPROPERTY()`
- L251 _public member_ `FTransform Parent;` — `UPROPERTY()`
- L253 _public function_ `FConstraintOffset() : Translation(FVector::ZeroVector) , Rotation(FQuat::Identity) , Scale(FVector::OneVector) , Parent(FTransform::Identity)`
- L261 _public prototype_ `void ApplyInverseOffset(const FTransform& InTarget, FTransform& OutSource) const;` — Apply the Inverse offset
- L263 _public prototype_ `void SaveInverseOffset(const FTransform& Source, const FTransform& Target, const FConstraintDescription& Operator);` — Save the Inverse offset
- L265 _public function_ `void Reset()` — Clear the offset

#### struct `FTransformConstraint`  
`struct FTransformConstraint`  
_L285-324_
- reflection: `USTRUCT(BlueprintType)`
- L292 _public member_ `FConstraintDescription Operator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Constraint")` — @note thought of separating this out per each but we'll have an issue with applying transform in what order but something to think about if that seems better
- L295 _public member_ `FName SourceNode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Constraint")`
- L298 _public member_ `FName TargetNode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Constraint")`
- L301 _public member_ `float Weight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Constraint")`
- L305 _public member_ `bool bMaintainOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Constraint")` — When the constraint is first applied, maintain the offset from the target node
- L307 _public function_ `FTransformConstraint() : SourceNode(NAME_None) , TargetNode(NAME_None) , Weight(1.f) , bMaintainOffset(true)`

#### enum `EConstraintType`  
`enum class EConstraintType : uint8`  
_L331-341_
- reflection: `UENUM(BlueprintType)`
- desc: Constraint Types
- L334 _public enumerator_ `Transform` — Transform Constraint
- L337 _public enumerator_ `Aim` — Aim Constraint
- L340 _public enumerator_ `MAX` — MAX - invalid

#### struct `FConstraintDescriptionEx`  
`struct FConstraintDescriptionEx`  
_L345-396_
- reflection: `USTRUCT()`
- desc: A description of how to apply a simple transform constraint
- L350 _public member_ `FFilterOptionPerAxis AxesFilterOption;` — `UPROPERTY(EditAnywhere, Category = FAimConstraintDescription)`
- L352 _public prototype_ `virtual ~FConstraintDescriptionEx() = default;`
- L365 _public prototype_ `virtual void AccumulateConstraintTransform(const FTransform& TargetTransform, const FTransform& CurrentTransform, const FTransform& CurrentParentTransform, float Weight, FMultiTransformBlendHelper& BlendHelperInLocalSpace) const PURE_VIRTUAL(AccumulateConstraintTransform, );` — Apply Constraint : Apply Constraint transform to BlendHelperInLocalSpace in local space @param Target Transform: Current Target Transform in global space @param Current Transform: Current Source Transform in global space @param Current Parent Transform: Current Source Parent Transform in global space @param Weight : Current Weight @param BlendHelperInLocalSpace : Blend Helper, this accumulates all constraints transform and later on blend to final transform @return BlendHelperInLocalSpace will contains constraint's local transform result, it is local because that's how you want to compose multiple to one transform at the end
- L372 _public function_ `virtual bool DoesAffectRotation() const` — Functions that describes what they modify Since same component will be blended by weight correctly, this has to split to each component
- L373 _public function_ `virtual bool DoesAffectTranslation() const`
- L374 _public function_ `virtual bool DoesAffectScale() const`
- L379 _public function_ `virtual bool DoesAffectTransform() const` — Functions that describes what they modify - this means, whole Transform, so combined transform, not individual component This will override any individual component if returning true
- L381 _public prototype_ `virtual FString GetDisplayString() const PURE_VIRTUAL(GetDisplayString, return TEXT("None"`
- L386 _public function_ `virtual void Serialize(FArchive& Ar)` — Serializer

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FConstraintDescriptionEx> : public TStructOpsTypeTraitsBase2<FConstraintDescriptionEx>`  
_L398-404_
- inherits: `TStructOpsTypeTraitsBase2<FConstraintDescriptionEx>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L401-403_

#### enum `ETransformConstraintType`  
`enum class ETransformConstraintType : uint8`  
_L408-415_
- reflection: `UENUM(Blueprintable)`
- desc: Transform Constraint Types
- L410 _public enumerator_ `Translation`
- L411 _public enumerator_ `Rotation`
- L412 _public enumerator_ `Scale`
- L413 _public enumerator_ `Parent`
- L414 _public enumerator_ `LookAt`

#### struct `FTransformConstraintDescription`  
`struct FTransformConstraintDescription : public FConstraintDescriptionEx`  
_L419-460_
- reflection: `USTRUCT()`
- inherits: `FConstraintDescriptionEx`
- desc: A description of how to apply a simple transform constraint
- L424 _public member_ `ETransformConstraintType TransformType;` — `UPROPERTY(EditAnywhere, Category = FAimConstraintDescription)`
- L426 _public function_ `FTransformConstraintDescription(const ETransformConstraintType InType = ETransformConstraintType::Translation) :TransformType (InType)`
- L430 _public prototype_ `virtual void AccumulateConstraintTransform(const FTransform& TargetTransform, const FTransform& CurrentTransform, const FTransform& CurrentParentTransform, float Weight, FMultiTransformBlendHelper& BlendHelperInLocalSpace) const override;`
- L431 _public function_ `virtual bool DoesAffectRotation() const override`
- L432 _public function_ `virtual bool DoesAffectTranslation() const override`
- L433 _public function_ `virtual bool DoesAffectScale() const override`
- L434 _public function_ `virtual bool DoesAffectTransform() const override`
- L436 _public function_ `virtual FString GetDisplayString() const override`
- L455 _public function_ `virtual void Serialize(FArchive& Ar) override`

#### struct `FAimConstraintDescription`  
`struct FAimConstraintDescription : public FConstraintDescriptionEx`  
_L464-500_
- reflection: `USTRUCT()`
- inherits: `FConstraintDescriptionEx`
- desc: A description of how to apply aim constraint
- L469 _public member_ `FAxis LookAt_Axis;` — `UPROPERTY(EditAnywhere, Category = FAimConstraintDescription)`
- L471 _public member_ `FAxis LookUp_Axis;` — `UPROPERTY(EditAnywhere, Category = FAimConstraintDescription)`
- L473 _public member_ `bool bUseLookUp;` — `UPROPERTY(EditAnywhere, Category = FAimConstraintDescription)`
- L475 _public member_ `FVector LookUpTarget;` — `UPROPERTY(EditAnywhere, Category = FAimConstraintDescription)`
- L477 _public function_ `FAimConstraintDescription() : LookAt_Axis() , LookUp_Axis(FVector::UpVector) , bUseLookUp(false) , LookUpTarget(ForceInitToZero)`
- L485 _public prototype_ `virtual void AccumulateConstraintTransform(const FTransform& TargetTransform, const FTransform& CurrentTransform, const FTransform& CurrentParentTransform, float Weight, FMultiTransformBlendHelper& BlendHelperInLocalSpace) const override;`
- L486 _public function_ `virtual bool DoesAffectRotation() const override`
- L487 _public function_ `virtual FString GetDisplayString() const override`
- L492 _public function_ `virtual void Serialize(FArchive& Ar) override`

#### struct `FConstraintDescriptor`  
`struct FConstraintDescriptor`  
_L509-679_
- reflection: `USTRUCT()`
- desc: Constraint data container. It contains union of Constraints and node will contain array of these. These are the one contained in NodeData, and it will be iterated via evaluate process The goal is to have contiguous memory location where they can iterate through linearly
- L514 _public member_ `EConstraintType Type;` — `UPROPERTY()`
- L516 _public member_ `FConstraintDescriptionEx* ConstraintDescription;`
- L518 _public function_ `FConstraintDescriptor() : Type(EConstraintType::MAX) , ConstraintDescription(nullptr)`
- L524 _public function_ `FConstraintDescriptor(const FTransformConstraintDescription& InT) : Type(EConstraintType::Transform) , ConstraintDescription(nullptr)`
- L531 _public function_ `FConstraintDescriptor(const FAimConstraintDescription& InA) : Type(EConstraintType::Aim) , ConstraintDescription(nullptr)`
- L538 _public function_ `FConstraintDescriptor(const FConstraintDescriptor& InOther) : ConstraintDescription(nullptr)`
- L544 _public function_ `FString GetDisplayString() const`
- L554 _public function_ `FConstraintDescriptor& operator=(const FConstraintDescriptor& Other)`
- L575 _private function_ `void Set(const FAimConstraintDescription& InA)`
- L581 _private function_ `void Set(const FTransformConstraintDescription& InT)`
- L587 _private function_ `void Clear()`
- L599 _public function_ `template <typename T> T* GetTypedConstraint() const` — this does not check type - we can, but that is hard to maintain, maybe I'll change later
- L604 _public function_ `~FConstraintDescriptor()`
- L632 _public function_ `bool IsValid() const`
- L636 _public function_ `bool DoesAffectRotation() const`
- L645 _public function_ `bool DoesAffectTranslation() const`
- L654 _public function_ `bool DoesAffectScale() const`
- L663 _public function_ `bool DoesAffectTransform() const`
- L672 _public function_ `void ApplyConstraintTransform(const FTransform& TargetTransform, const FTransform& CurrentTransform, const FTransform& CurrentParentTransform, float Weight, FMultiTransformBlendHelper& BlendHelperInLocalSpace) const`

#### struct `FConstraintData`  
`struct FConstraintData`  
_L686-744_
- reflection: `USTRUCT()`
- desc: Constraint Data that is contained in Node Datat You can have as many of these per node
- L692 _public member_ `FConstraintDescriptor Constraint;` — `UPROPERTY()` — Constraint Description
- L695 _public member_ `float Weight;` — `UPROPERTY()` — Weight of the constraint
- L698 _public member_ `bool bMaintainOffset;` — `UPROPERTY()` — When the constraint is first applied, maintain the offset from the target node
- L701 _public member_ `FTransform Offset;` — `UPROPERTY()` — Constraint offset if bMaintainOffset is used
- L704 _public member_ `FTransform CurrentTransform;` — `UPROPERTY(transient)`
- L706 _public function_ `FConstraintData() : Weight(1.f) , bMaintainOffset(true) , Offset(FTransform::Identity)`
- L712 _public function_ `FConstraintData(const FTransformConstraintDescription& InTrans, FName InTargetNode = NAME_None, float InWeight = 1.f, bool bInMaintainOffset = true, const FTransform& InOffset = FTransform::Identity) : Constraint(InTrans) , Weight(InWeight) , bMaintainOffset(bInMaintainOffset) , Offset(InOffset)`
- L719 _public function_ `FConstraintData(const FAimConstraintDescription& InAim, FName InTargetNode = NAME_None, float InWeight = 1.f, bool bInMaintainOffset = true, const FTransform& InOffset = FTransform::Identity) : Constraint(InAim) , Weight(InWeight) , bMaintainOffset(bInMaintainOffset) , Offset(InOffset)`
- L736 _public prototype_ `void ApplyInverseOffset(const FTransform& InTarget, FTransform& OutSource, const FTransform& InBaseTransform) const;`
- L737 _public prototype_ `void SaveInverseOffset(const FTransform& Source, const FTransform& Target, const FTransform& InBaseTransform);`
- L738 _public function_ `void ResetOffset()`
- L743 _public prototype_ `void ApplyConstraintTransform(const FTransform& TargetTransform, const FTransform& InCurrentTransform, const FTransform& CurrentParentTransform, FMultiTransformBlendHelper& BlendHelperInLocalSpace) const;`

#### Free symbols / members of external scopes

- L112 _function_ `friend FArchive & operator<<(FArchive & Ar, FFilterOptionPerAxis & D)`
- L216 _function_ `friend FArchive & operator<<(FArchive & Ar, FConstraintDescription & D)`
- L273 _function_ `friend FArchive & operator<<(FArchive & Ar, FConstraintOffset & D)`
- L314 _function_ `friend FArchive & operator<<(FArchive & Ar, FTransformConstraint & D)`
- L391 _function_ `friend FArchive & operator<<(FArchive & Ar, FConstraintDescriptionEx & D)`
- L402 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon9a9f05aa0103`)
- L608 _function_ `friend FArchive & operator<<(FArchive & Ar, FConstraintDescriptor & D)`
- L726 _function_ `friend FArchive & operator<<(FArchive & Ar, FConstraintData & D)`

### `Source/Runtime/AnimationCore/Public/EulerTransform.h` (Public)


#### enum `EEulerRotationOrder`  
`enum class EEulerRotationOrder : uint8`  
_L20-28_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `XYZ`
- L23 _public enumerator_ `XZY`
- L24 _public enumerator_ `YXZ`
- L25 _public enumerator_ `YZX`
- L26 _public enumerator_ `ZXY`
- L27 _public enumerator_ `ZYX`

#### struct `FEulerTransform`  
`struct FEulerTransform`  
_L31-114_
- reflection: `USTRUCT(BlueprintType)`
- L35 _public typedef_ `typedef FVector::FReal FReal;`
- L40 _public member_ `static const FEulerTransform Identity;` — The identity transformation (Rotation = FRotator::ZeroRotator, Translation = FVector::ZeroVector, Scale = (1,1,1)).
- L42 _public function_ `inline FEulerTransform() : Location(ForceInitToZero) , Rotation(ForceInitToZero) , Scale(FVector::OneVector)`
- L49 _public function_ `inline FEulerTransform(const FVector& InLocation, const FRotator& InRotation, const FVector& InScale) : Location(InLocation) , Rotation(InRotation) , Scale(InScale)`
- L56 _public function_ `inline FEulerTransform(const FRotator& InRotation, const FVector& InLocation, const FVector& InScale) : Location(InLocation) , Rotation(InRotation) , Scale(InScale)`
- L63 _public function_ `inline explicit FEulerTransform(const FTransform& InTransform) : Location(InTransform.GetLocation()) , Rotation(InTransform.GetRotation().Rotator()) , Scale(InTransform.GetScale3D())`
- L73 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Transform")` — The translation of this transform
- L77 _public member_ `FRotator Rotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Transform")` — The rotation of this transform
- L81 _public member_ `FVector Scale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Transform")` — The scale of this transform
- L84 _public function_ `inline FTransform ToFTransform() const` — Convert to an FTransform
- L90 _public function_ `inline void FromFTransform(const FTransform& InTransform)` — Convert from an FTransform
- L98 _public function_ `inline bool Equals(const FEulerTransform& Other, FReal Tolerance = KINDA_SMALL_NUMBER) const` — Test if all components of the transforms are equal, within a tolerance.
- L105 _public function_ `inline const FVector& GetLocation() const`
- L106 _public function_ `inline FQuat GetRotation() const`
- L107 _public function_ `inline const FRotator& Rotator() const`
- L108 _public function_ `inline const FVector& GetScale3D() const`
- L109 _public function_ `inline void SetLocation(const FVector& InValue)`
- L110 _public function_ `inline void SetRotation(const FQuat& InValue)`
- L111 _public function_ `inline void SetRotator(const FRotator& InValue)`
- L112 _public function_ `inline void SetScale3D(const FVector& InValue)`
- L113 _public function_ `inline void NormalizeRotation()`

#### struct `TBaseStructure`  
`template<> struct TBaseStructure<FEulerTransform>`  
_L116-119_
- L118 _public function_ `static UScriptStruct* Get()`

### `Source/Runtime/AnimationCore/Public/FABRIK.h` (Public)


#### struct `FFABRIKChainLink`  
`struct FFABRIKChainLink`  
_L24-83_
- reflection: `USTRUCT()`
- desc: Transient structure for FABRIK node evaluation
- L30 _public member_ `FVector Position;` — Position of bone in component space.
- L33 _public member_ `double Length;` — Distance to its parent link.
- L36 _public member_ `int32 BoneIndex;` — Bone Index in SkeletalMesh
- L39 _public member_ `int32 TransformIndex;` — Transform Index that this control will output
- L42 _public member_ `FVector DefaultDirToParent;` — Default Direction to Parent
- L46 _public member_ `TArray<int32> ChildZeroLengthTransformIndices;` — Child bones which are overlapping this bone. They have a zero length distance, so they will inherit this bone's transformation.
- L48 _public function_ `FFABRIKChainLink() : Position(FVector::ZeroVector) , Length(0.0) , BoneIndex(INDEX_NONE) , TransformIndex(INDEX_NONE) , DefaultDirToParent(FVector(-1.0, 0.0, 0.0))`
- L57 _public function_ `FFABRIKChainLink(const FVector& InPosition, const double InLength, const FCompactPoseBoneIndex& InBoneIndex, const int32& InTransformIndex) : Position(InPosition) , Length(InLength) , BoneIndex(InBoneIndex.GetInt()) , TransformIndex(InTransformIndex) , DefaultDirToParent(FVector(-1.0, 0.0, 0.0))`
- L66 _public function_ `FFABRIKChainLink(const FVector& InPosition, const double InLength, const FCompactPoseBoneIndex& InBoneIndex, const int32& InTransformIndex, const FVector& InDefaultDirToParent) : Position(InPosition) , Length(InLength) , BoneIndex(InBoneIndex.GetInt()) , TransformIndex(InTransformIndex) , DefaultDirToParent(InDefaultDirToParent)`
- L75 _public function_ `FFABRIKChainLink(const FVector& InPosition, const double InLength, const int32 InBoneIndex, const int32 InTransformIndex) : Position(InPosition) , Length(InLength) , BoneIndex(InBoneIndex) , TransformIndex(InTransformIndex) , DefaultDirToParent(FVector(-1.0, 0.0, 0.0))`

#### Free symbols / members of external scopes

- L85 _namespace_ `namespace AnimationCore`
- L100 _prototype_ `bool SolveFabrik(TArray<FFABRIKChainLink>& InOutChain, const FVector& TargetPosition, double MaximumReach, double Precision, int32 MaxIteration);` (scope `AnimationCore`) — Fabrik solver This solves FABRIK @param	Chain				Array of chain data @param	TargetPosition		Target for the IK @param	MaximumReach		Maximum Reach @param	Precision			Precision @param	MaxIteration		Number of Max Iteration @return  true if modified. False if not.

### `Source/Runtime/AnimationCore/Public/NodeChain.h` (Public)


#### struct `FNodeChain`  
`struct FNodeChain`  
_L10-16_
- reflection: `USTRUCT()`
- desc: A chain of nodes in a hierarchy
- L15 _public member_ `TArray<FName> Nodes;` — `UPROPERTY()`

### `Source/Runtime/AnimationCore/Public/NodeHierarchy.h` (Public)


#### struct `FNodeObject`  
`struct FNodeObject`  
_L13-34_
- reflection: `USTRUCT()`
- desc: A node in a named hierarchy
- L17 _public function_ `FNodeObject() : Name(NAME_None) , ParentName(NAME_None)`
- L22 _public function_ `FNodeObject(const FName& InName, const FName& InParentName) : Name(InName) , ParentName(InParentName)`
- L29 _public member_ `FName Name;` — `UPROPERTY()` — The name of this node
- L33 _public member_ `FName ParentName;` — `UPROPERTY()` — The name of this node's parent

#### struct `FNodeHierarchyData`  
`struct FNodeHierarchyData`  
_L38-195_
- reflection: `USTRUCT()`
- desc: Hierarchy of nodes
- L44 _public member_ `TArray<FNodeObject> Nodes;` — `UPROPERTY()` — Node hierarchy data
- L48 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY()` — Node transform data
- L52 _public member_ `TMap<FName, int32> NodeNameToIndexMapping;` — `UPROPERTY()` — Transient look up mapping from name to index to array
- L55 _public function_ `const FTransform& GetTransform(int32 Index) const`
- L60 _public function_ `FTransform& GetTransform(int32 Index)`
- L65 _public function_ `void SetTransform(int32 Index, const FTransform& NewTransform)`
- L71 _public function_ `int32 GetParentIndex(int32 Index) const`
- L76 _public function_ `FName GetParentName(int32 Index) const`
- L81 _public function_ `void SetParentName(int32 Index, FName NewParent)`
- L86 _public function_ `int32 GetNodeIndex(const FName& NodeName) const`
- L92 _public function_ `FName GetNodeName(int32 Index) const`
- L97 _public function_ `void SetNodeName(int32 Index, const FName& NewNodeName)`
- L114 _public function_ `int32 Add(const FName& InNodeName, const FName& InParentName, const FTransform& InTransform)`
- L138 _public function_ `void Empty(int32 Size = 0)`
- L145 _public function_ `void Allocate(int32 Size)`
- L151 _public function_ `int32 Num() const` — Returns number of bones in Skeleton.
- L156 _public function_ `bool IsValidIndex(int32 Index) const`
- L161 _public function_ `int32 Remove(const FName& InNodeName)`
- L183 _public function_ `void BuildNodeNameToIndexMapping()`

#### struct `FNodeHierarchyWithUserData`  
`struct FNodeHierarchyWithUserData`  
_L198-404_
- reflection: `USTRUCT()`
- L204 _protected member_ `FNodeHierarchyData Hierarchy;` — `UPROPERTY()`
- L207 _public prototype_ `virtual ~FNodeHierarchyWithUserData() = default;`
- L209 _public function_ `const FNodeHierarchyData& GetHierarchy() const`
- L210 _public function_ `const TArray<FTransform>& GetTransforms() const`
- L211 _public function_ `TArray<FTransform>& GetTransforms()`
- L212 _public function_ `const TArray<FNodeObject>& GetNodes() const`
- L215 _public function_ `template<typename DataType> const DataType& GetNodeData(int32 Index) const`
- L218 _public function_ `template<typename DataType> DataType& GetNodeData(int32 Index)`
- L221 _public function_ `virtual const FTransform& GetLocalTransform(int32 Index) const PURE_VIRTUAL(FNodeHierarchyWithUserData::GetLocalTransform, return Hierarchy.Transforms[Index];) virtual const FTransform& GetGlobalTransform(int32 Index) const PURE_VIRTUAL(FNodeHierarchyWithUserData::GetGlobalTransform, return Hierarchy.Transforms[Index];) virtual FTransform& GetLocalTransform(int32 Index) PURE_VIRTUAL(FNodeHierarchyWithUserData::GetLocalTransform, return Hierarchy.Transforms[Index];) virtual FTransform& GetGlobalTransform(int32 Index) PURE_VIRTUAL(FNodeHierarchyWithUserData::GetGlobalTransform, return Hierarchy.Transforms[Index];) virtual void SetLocalTransform(int32 Index, const FTransform& NewTransform)` — it's up to your hierarchy to decide what to do with this
- L226 _public function_ `virtual void SetGlobalTransform(int32 Index, const FTransform& NewTransform)`
- L229 _public function_ `TArray<FName> GetChildren(int32 Index) const` — get all list of children
- L244 _public function_ `FTransform GetLocalTransformByName(const FName& NodeName) const`
- L255 _public function_ `FTransform GetGlobalTransformByName(const FName& NodeName) const`
- L266 _public function_ `void SetLocalTransformByName(const FName& NodeName, const FTransform& NewTransform)`
- L275 _public function_ `void SetGlobalTransformByName(const FName& NodeName, const FTransform& NewTransform)`
- L284 _public function_ `virtual void Initialize()` — should initialize all transient data for fast look up
- L289 _public function_ `int32 GetParentIndex(int32 Index) const`
- L294 _public function_ `FName GetParentName(int32 Index) const`
- L299 _public function_ `FName GetParentName(const FName& NodeName) const`
- L310 _public function_ `void SetParentName(int32 Index, FName NewParent)`
- L319 _public function_ `int32 GetNodeIndex(const FName& InNodeName) const`
- L324 _public function_ `FName GetNodeName(int32 Index) const`
- L329 _public function_ `void SetNodeName(int32 Index, const FName& NewNode)`
- L334 _public function_ `int32 Add(const FName& InNodeName, const FName& InParentName, const FTransform& InTransform)`
- L341 _public function_ `template<typename DataType> int32 Add(const FName& InNodeName, const FName& InParentName, const FTransform& InTransform, const DataType& InNodeData)`
- L355 _public function_ `void Remove(const FName& InNodeName)`
- L369 _public function_ `void Empty(int32 Size = 0)`
- L380 _public function_ `int32 GetNum() const`
- L385 _public function_ `bool IsValidIndex(int32 Index) const`
- L390 _public function_ `bool Contains(const FName InNodeName) const`
- L397 _protected function_ `virtual const void* GetUserDataImpl(int32 Index) const` — Derived classes can implement this to supply per-node user data
- L398 _protected function_ `virtual void* GetUserDataImpl(int32 Index)`
- L399 _protected function_ `virtual int32 AddUserDataImpl(const void* InData)`
- L400 _protected function_ `virtual int32 GetNumUserData() const`
- L401 _protected function_ `virtual void EmptyUserData(int32 Size = 0)`
- L402 _protected function_ `virtual void RemoveUserData(int32 Index)`
- L403 _protected function_ `virtual bool HasUserData() const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNodeHierarchyWithUserData> : public TStructOpsTypeTraitsBase2<FNodeHierarchyWithUserData>`  
_L407-413_
- inherits: `TStructOpsTypeTraitsBase2<FNodeHierarchyWithUserData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L410-412_

#### Free symbols / members of external scopes

- L411 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anonf0bc0daa0103`)

### `Source/Runtime/AnimationCore/Public/SoftIK.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AnimationCore`
- L24 _prototype_ `void SoftenIKEffectorPosition( const FVector& RootLocation, const float TotalChainLength, const float SoftLengthPercent, const float Alpha, FVector& InOutEffectorPosition);` (scope `AnimationCore`) — Soft IK This modifies the effector position for a chain of joints being controlled by IK by making the effector softly approach full extension. It takes the desired effector position and adjusts it according to an exponential falloff as the effector approach the full length of the chain. The technique used is described here: https://web.archive.org/web/20160610183037/https://softimageblog.com/archives/108 @param RootLocation			The location of the bone at the root of the chain @param TotalChainLength		The total length of the chain from root to tip, along the bones (not straight line). @param SoftLengthPercent		The percentage of the chain length to begin softening the effector motion (typically set to 0.97) @param Alpha					The amount of softness to apply (0 is none, 1 is full amount). Default is 1. @param InOutEffectorPosition	The input position of the end effector. This is modified by this function to "soften" the IK.

### `Source/Runtime/AnimationCore/Public/SplineIK.h` (Public)


#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(float, FFloatMapping, float);` — Outputs a float given a float input
- L18 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(float, FFloatMapping, float);` — Outputs a float given a float input
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(float, FFindParamAtFirstSphereIntersection, const FVector& , float , int32& ) namespace AnimationCore { void SolveSplineIK(const TArray<FTransform>& BoneTransforms, const FInterpCurveVector& PositionSpline, const FInterpCurveQuat& RotationSpline, const FInterpCurveVector& ScaleSpline, const float TotalSplineAlpha, const float TotalSplineLength, const FFloatMapping& Twist, const float Roll, const float Stretch, const float Offset, const EAxis::Type BoneAxis, const FFindParamAtFirstSphereIntersection& FindParamAtFirstSphereIntersection, const TArray<FQuat>& BoneOffsetRotations, const TArray<float>& BoneLengths, const float OriginalSplineLength, TArray<FTransform>& OutBoneTransforms); };` — Finds a spline parameter (alpha) at the intersection of a spline and a sphere. Used by SolveSplineIK. The assumption is that the sphere's origin lies on the spline and the StartingLinearIndex is used to skip ahead when using a linear approximation to the spline. @param	InOriginOnSpline			Sphere origin on the spline @param	InRadius					Sphere radius @param	InOutStartingLinearIndex	(inout) The index of the linear approximation to start at. After the function returns this should be set to a value that can be passed into the next call to accelerate subsequent queries.
- L30 _namespace_ `namespace AnimationCore`
- L35 _prototype_ `void SolveSplineIK(const TArray<FTransform>& BoneTransforms, const FInterpCurveVector& PositionSpline, const FInterpCurveQuat& RotationSpline, const FInterpCurveVector& ScaleSpline, const float TotalSplineAlpha, const float TotalSplineLength, const FFloatMapping& Twist, const float Roll, const float Stretch, const float Offset, const EAxis::Type BoneAxis, const FFindParamAtFirstSphereIntersection& FindParamAtFirstSphereIntersection, const TArray<FQuat>& BoneOffsetRotations, const TArray<float>& BoneLengths, const float OriginalSplineLength, TArray<FTransform>& OutBoneTransforms);` (scope `AnimationCore`) — Spline IK

### `Source/Runtime/AnimationCore/Public/TransformNoScale.h` (Public)


#### struct `FTransformNoScale`  
`struct FTransformNoScale`  
_L16-74_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `static const FTransformNoScale Identity;` — The identity transformation (Rotation = FRotator::ZeroRotator, Translation = FVector::ZeroVector, Scale = (1,1,1)).
- L25 _public function_ `inline FTransformNoScale() : Location(ForceInitToZero) , Rotation(ForceInitToZero)`
- L31 _public function_ `inline FTransformNoScale(const FVector& InLocation, const FQuat& InRotation) : Location(InLocation) , Rotation(InRotation)`
- L37 _public function_ `inline FTransformNoScale(const FTransform& InTransform) : Location(InTransform.GetLocation()) , Rotation(InTransform.GetRotation())`
- L43 _public function_ `inline FTransformNoScale& operator =(const FTransform& InTransform)`
- L49 _public function_ `inline operator FTransform() const`
- L56 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Transform")` — The translation of this transform
- L60 _public member_ `FQuat Rotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Transform")` — The rotation of this transform
- L63 _public function_ `inline FTransform ToFTransform() const` — Convert to an FTransform
- L69 _public function_ `inline void FromFTransform(const FTransform& InTransform)` — Convert from an FTransform

### `Source/Runtime/AnimationCore/Public/TwoBoneIK.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AnimationCore`
- L29 _prototype_ `void SolveTwoBoneIK(const FVector& RootPos, const FVector& JointPos, const FVector& EndPos, const FVector& JointTarget, const FVector& Effector, FVector& OutJointPos, FVector& OutEndPos, bool bAllowStretching, double StartStretchRatio, double MaxStretchScale);` (scope `AnimationCore`) — Two Bone IK This handles two bone chain link excluding root bone. This will solve the solution for joint/end when given root, joint, end position (root->joint->end in the hierarchy) based on effector, joint target location This only solves for location, if you want to rotate them to face target, this doesn't do it for you @param	RootPos				Root position @param	JointPos			Joint position @param	EndPos				End position @param	JointTarget			Joint Target position (where joint is facing while creating plane between joint pos, joint target, root pos(rotate-plane ik)) @param	Effector			Effector position (target position) @param	OutJointPos			(out) adjusted joint pos @param	OutEndPos			(out) adjusted end pos @param	bAllowStretching	whether or not to allow stretching or not @param	StartStretchRatio	When should it start stretch -i.e. 1 means its own length without any stretch @param	MaxStretchScale		How much it can stretch to in ratio
- L49 _prototype_ `void SolveTwoBoneIK(const FVector& RootPos, const FVector& JointPos, const FVector& EndPos, const FVector& JointTarget, const FVector& Effector, FVector& OutJointPos, FVector& OutEndPos, double UpperLimbLength, double LowerLimbLength, bool bAllowStretching, double StartStretchRatio, double MaxStretchScale);` (scope `AnimationCore`) — Two Bone IK This handles two bone chain link excluding root bone. This will solve the solution for joint/end when given root, joint, end position (root->joint->end in the hierarchy) based on effector, joint target location This only solves for location, if you want to rotate them to face target, this doesn't do it for you @param	RootPos				Root position @param	JointPos			Joint position @param	EndPos				End position @param	JointTarget			Joint Target position (where joint is facing while creating plane between joint pos, joint target, root pos(rotate-plane ik)) @param	Effector			Effector position (target position) @param	OutJointPos			(out) adjusted joint pos @param	OutEndPos			(out) adjusted end pos @param	bAllowStretching	whether or not to allow stretching or not								  O @param	StartStretchRatio	When should it start stretch -i.e. 1 means its own length without any stretch @param	MaxStretchScale		How much it can stretch to in ratio
- L69 _prototype_ `void SolveTwoBoneIK(FTransform& InOutRootTransform, FTransform& InOutJointTransform, FTransform& InOutEndTransform, const FVector& JointTarget, const FVector& Effector, bool bAllowStretching, double StartStretchRatio, double MaxStretchScale);` (scope `AnimationCore`) — Two Bone IK This handles two bone chain link excluding root bone. This will solve the solution for joint/end when given root, joint, end position (root->joint->end in the hierarchy) based on effector, joint target location This only solves for location, if you want to rotate them to face target, this doesn't do it for you @param	RootPos				Root position @param	JointPos			Joint position @param	EndPos				End position @param	JointTarget			Joint Target position (where joint is facing while creating plane between joint pos, joint target, root pos(rotate-plane ik)) @param	Effector			Effector position (target position) @param	OutJointPos			(out) adjusted joint pos @param	OutEndPos			(out) adjusted end pos @param	bAllowStretching	whether or not to allow stretching or not @param	StartStretchRatio	When should it start stretch -i.e. 1 means its own length without any stretch @param	MaxStretchScale		How much it can stretch to in ratio
- L89 _prototype_ `void SolveTwoBoneIK(FTransform& InOutRootTransform, FTransform& InOutJointTransform, FTransform& InOutEndTransform, const FVector& JointTarget, const FVector& Effector, double UpperLimbLength, double LowerLimbLength, bool bAllowStretching, double StartStretchRatio, double MaxStretchScale);` (scope `AnimationCore`) — Two Bone IK This handles two bone chain link excluding root bone. This will solve the solution for joint/end when given root, joint, end position (root->joint->end in the hierarchy) based on effector, joint target location This only solves for location, if you want to rotate them to face target, this doesn't do it for you @param	RootPos				Root position @param	JointPos			Joint position @param	EndPos				End position @param	JointTarget			Joint Target position (where joint is facing while creating plane between joint pos, joint target, root pos(rotate-plane ik)) @param	Effector			Effector position (target position) @param	OutJointPos			(out) adjusted joint pos @param	OutEndPos			(out) adjusted end pos @param	bAllowStretching	whether or not to allow stretching or not @param	StartStretchRatio	When should it start stretch -i.e. 1 means its own length without any stretch @param	MaxStretchScale		How much it can stretch to in ratio
