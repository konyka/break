# Plugins / Learning

- module root: `Plugins/Experimental/LearningCore/Source/Learning`
- headers: 24; symbols: 1631
- symbol kinds: class=7, enum=12, enumerator=55, function=200, macro=37, member=438, namespace=69, prototype=663, struct=126, typedef=22, variable=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, JsonUtilities, NNE, NNERuntimeBasicCpu
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/LearningCore/Source/Learning/Private/LearningEigen.h` (Private)


#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_LEARNING_EIGEN_DEBUG_ENABLE (!UE_BUILD_SHIPPING)` — Enables or disables various Eigen debugging related functionality. In general there is not much harm in enabling this since it does not perform expensive checks however this can still be disabled in editor mode to give some small improvement to performance
- L30 _macro_ `#define EIGEN_MPL2_ONLY`
- L41 _macro_ `#define eigen_assert(x) check(x)`
- L48 _macro_ `#define EIGEN_NO_DEBUG`
- L68 _namespace_ `namespace Eigen`
- L71 _typedef_ `using RowMajorMatrixXf = Matrix<float, Dynamic, Dynamic, RowMajor>;` (scope `Eigen`) — RowMajor matrix type we can use to Map our C-like array to Eigen
- L74 _typedef_ `using RowMajorArrayXXf = Array<float, Dynamic, Dynamic, RowMajor>;` (scope `Eigen`) — RowMajor 2D array type we can use to Map our C-like array to Eigen
- L77 _function_ `static FORCEINLINE const TCHAR* ComputationInfoString(ComputationInfo Info)` (scope `Eigen`) — Computation info enum to string mapping
- L94 _macro_ `#define InEigenVector(Array) Eigen::Map<const Eigen::VectorXf>(Array.GetData(), Eigen::Index(Array.Num()))`
- L95 _macro_ `#define InEigenRowVector(Array) Eigen::Map<const Eigen::RowVectorXf>(Array.GetData(), Eigen::Index(Array.Num()))`
- L96 _macro_ `#define InEigenArray1D(Array) Eigen::Map<const Eigen::ArrayXf>(Array.GetData(), Eigen::Index(Array.Num()))`
- L97 _macro_ `#define InEigenMatrix(Array) Eigen::Map<const Eigen::RowMajorMatrixXf>(Array.GetData(), Eigen::Index(Array.Num<0>()), Eigen::Index(Array.Num<1>()))`
- L98 _macro_ `#define InEigenColMatrix(Array) Eigen::Map<const Eigen::MatrixXf>(Array.GetData(), Eigen::Index(Array.Num<0>()), Eigen::Index(Array.Num<1>()))`
- L99 _macro_ `#define InEigenArray2D(Array) Eigen::Map<const Eigen::RowMajorArrayXXf>(Array.GetData(), Eigen::Index(Array.Num<0>()), Eigen::Index(Array.Num<1>()))`
- L100 _macro_ `#define InEigenColArray2D(Array) Eigen::Map<const Eigen::ArrayXXf>(Array.GetData(), Eigen::Index(Array.Num<0>()), Eigen::Index(Array.Num<1>()))`
- L102 _macro_ `#define OutEigenVector(Array) Eigen::Map<Eigen::VectorXf>(Array.GetData(), Eigen::Index(Array.Num()))`
- L103 _macro_ `#define OutEigenArray1D(Array) Eigen::Map<Eigen::ArrayXf>(Array.GetData(), Eigen::Index(Array.Num()))`
- L104 _macro_ `#define OutEigenMatrix(Array) Eigen::Map<Eigen::RowMajorMatrixXf>(Array.GetData(), Eigen::Index(Array.Num<0>()), Eigen::Index(Array.Num<1>()))`
- L105 _macro_ `#define OutEigenColMatrix(Array) Eigen::Map<Eigen::MatrixXf>(Array.GetData(), Eigen::Index(Array.Num<0>()), Eigen::Index(Array.Num<1>()))`
- L106 _macro_ `#define OutEigenArray2D(Array) Eigen::Map<Eigen::RowMajorArrayXXf>(Array.GetData(), Eigen::Index(Array.Num<0>()), Eigen::Index(Array.Num<1>()))`
- L107 _macro_ `#define OutEigenColArray2D(Array) Eigen::Map<Eigen::ArrayXXf>(Array.GetData(), Eigen::Index(Array.Num<0>()), Eigen::Index(Array.Num<1>()))`

### `Plugins/Experimental/LearningCore/Source/Learning/Public/Learning.h` (Public)


#### class `FLearningModule`  
`class FLearningModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningAction.h` (Public)


#### enum `UE::Learning::Action::EType`  
`enum class EType : uint8`  
_L24-58_
- desc: Action Type The core type of an action object for which different loss functions and behaviors are defined.
- L27 _public enumerator_ `Null = 0` — Empty Action
- L30 _public enumerator_ `Continuous = 1` — Vector of continuous float actions
- L33 _public enumerator_ `DiscreteExclusive = 2` — Set of exclusive discrete actions
- L36 _public enumerator_ `DiscreteInclusive = 3` — Set of inclusive discrete actions
- L39 _public enumerator_ `NamedDiscreteExclusive = 4` — Set of named exclusive discrete actions
- L42 _public enumerator_ `NamedDiscreteInclusive = 5` — Set of named inclusive discrete actions
- L45 _public enumerator_ `And = 6` — Combination of multiple actions
- L48 _public enumerator_ `OrExclusive = 7` — Exclusive choice from a set of actions
- L51 _public enumerator_ `OrInclusive = 8` — Inclusive choice from a set of actions
- L54 _public enumerator_ `Array = 9` — Fixed sized array of actions
- L57 _public enumerator_ `Encoding = 10` — Encoding of another action

#### enum `UE::Learning::Action::ENormalization`  
`enum class ENormalization : uint8`  
_L60-65_
- L62 _public enumerator_ `Manual = 0`
- L63 _public enumerator_ `AutoShared = 1`
- L64 _public enumerator_ `AutoPerDimension = 2`

#### struct `UE::Learning::Action::FSchemaElement`  
`struct FSchemaElement`  
_L84-84_
- desc: Action Schema Element A single element in the action schema representing a part of an action. Internally this consists of a index used by the schema to look up the associated action data and a generation id which can be used to check when this index is no longer valid.
- L84 _public member_ `struct FSchemaElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Action Schema Element A single element in the action schema representing a part of an action. Internally this consists of a index used by the schema to look up the associated action data and a generation id which can be used to check when this index is no longer valid.
- L84 _public member_ `struct FSchemaElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Action Schema Element A single element in the action schema representing a part of an action. Internally this consists of a index used by the schema to look up the associated action data and a generation id which can be used to check when this index is no longer valid.

#### struct `UE::Learning::Action::FSchemaContinuousParameters`  
`struct FSchemaContinuousParameters`  
_L86-99_
- L89 _public member_ `int32 Num = 0;` — Number of values in the continuous action
- L92 _public member_ `TArrayView<const float> Scales;` — Per-element standard deviation values for normalization. If empty, identity scaling is applied. *Only used when normalization option is set to manual.
- L95 _public member_ `TArrayView<const float> Offsets;` — Per-element mean values for normalization. If empty, zero bias is applied. *Only used when normalization option is set to manual.
- L98 _public member_ `ENormalization NormalizationOption = ENormalization::Manual;` — The normalization option to use.

#### struct `UE::Learning::Action::FSchemaDiscreteExclusiveParameters`  
`struct FSchemaDiscreteExclusiveParameters`  
_L101-108_
- L104 _public member_ `int32 Num = 0;` — Number of choices in the discrete action
- L107 _public member_ `TArrayView<const float> PriorProbabilities;` — Prior Probabilities of the discrete actions.

#### struct `UE::Learning::Action::FSchemaDiscreteInclusiveParameters`  
`struct FSchemaDiscreteInclusiveParameters`  
_L110-117_
- L113 _public member_ `int32 Num = 0;` — Number of choices in the discrete action
- L116 _public member_ `TArrayView<const float> PriorProbabilities;` — Prior Probabilities of the discrete actions.

#### struct `UE::Learning::Action::FSchemaNamedDiscreteExclusiveParameters`  
`struct FSchemaNamedDiscreteExclusiveParameters`  
_L119-126_
- L122 _public member_ `TArrayView<const FName> ElementNames;` — Names of the discrete actions.
- L125 _public member_ `TArrayView<const float> PriorProbabilities;` — Prior Probabilities of the discrete actions.

#### struct `UE::Learning::Action::FSchemaNamedDiscreteInclusiveParameters`  
`struct FSchemaNamedDiscreteInclusiveParameters`  
_L128-135_
- L131 _public member_ `TArrayView<const FName> ElementNames;` — Names of the discrete actions.
- L134 _public member_ `TArrayView<const float> PriorProbabilities;` — Prior Probabilities of the discrete actions.

#### struct `UE::Learning::Action::FSchemaAndParameters`  
`struct FSchemaAndParameters`  
_L137-144_
- L140 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sub-actions.
- L143 _public member_ `TArrayView<const FSchemaElement> Elements;` — The associated sub-elements.

#### struct `UE::Learning::Action::FSchemaOrExclusiveParameters`  
`struct FSchemaOrExclusiveParameters`  
_L146-156_
- L149 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sub-actions.
- L152 _public member_ `TArrayView<const FSchemaElement> Elements;` — The associated sub-elements.
- L155 _public member_ `TArrayView<const float> PriorProbabilities;` — Prior Probabilities of the sub-actions.

#### struct `UE::Learning::Action::FSchemaOrInclusiveParameters`  
`struct FSchemaOrInclusiveParameters`  
_L158-168_
- L161 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sub-actions.
- L164 _public member_ `TArrayView<const FSchemaElement> Elements;` — The associated sub-elements.
- L167 _public member_ `TArrayView<const float> PriorProbabilities;` — Prior Probabilities of the sub-actions.

#### struct `UE::Learning::Action::FSchemaArrayParameters`  
`struct FSchemaArrayParameters`  
_L170-177_
- L173 _public member_ `FSchemaElement Element;` — The array sub-element.
- L176 _public member_ `int32 Num = 0;` — The number of elements in the array.

#### enum `UE::Learning::Action::EEncodingActivationFunction`  
`enum class EEncodingActivationFunction : uint8`  
_L180-186_
- desc: Activation Function to use for encoding
- L182 _public enumerator_ `ELU = 0`
- L183 _public enumerator_ `ReLU = 1`
- L184 _public enumerator_ `TanH = 2`
- L185 _public enumerator_ `GELU = 3`

#### struct `UE::Learning::Action::FSchemaEncodingParameters`  
`struct FSchemaEncodingParameters`  
_L200-213_
- L203 _public member_ `FSchemaElement Element;` — The sub-element.
- L206 _public member_ `int32 EncodingSize = 32;` — The size at which the sub-element should be encoded.
- L209 _public member_ `int32 LayerNum = 1;` — The number of layers in the encoding
- L212 _public member_ `EEncodingActivationFunction ActivationFunction = EEncodingActivationFunction::ELU;` — The activation function to use for encoding

#### struct `UE::Learning::Action::FSchema`  
`struct FSchema`  
_L222-388_
- desc: Action Schema This object allows you to construct a description of the kind of actions you might want to be generated by a policy. Internally this object contains a pool of individual elements. This allows them to be constructed performantly and in a cache efficient way. This object is therefore required to access any data about the individual action elements that are created.
- L224 _public prototype_ `FSchemaElement CreateNull(const FName Tag = NAME_None);`
- L225 _public prototype_ `FSchemaElement CreateContinuous(const FSchemaContinuousParameters Parameters, const FName Tag = NAME_None);`
- L226 _public prototype_ `FSchemaElement CreateDiscreteExclusive(const FSchemaDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L227 _public prototype_ `FSchemaElement CreateDiscreteInclusive(const FSchemaDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L228 _public prototype_ `FSchemaElement CreateNamedDiscreteExclusive(const FSchemaNamedDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L229 _public prototype_ `FSchemaElement CreateNamedDiscreteInclusive(const FSchemaNamedDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L230 _public prototype_ `FSchemaElement CreateAnd(const FSchemaAndParameters Parameters, const FName Tag = NAME_None);`
- L231 _public prototype_ `FSchemaElement CreateOrExclusive(const FSchemaOrExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L232 _public prototype_ `FSchemaElement CreateOrInclusive(const FSchemaOrInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L233 _public prototype_ `FSchemaElement CreateArray(const FSchemaArrayParameters Parameters, const FName Tag = NAME_None);`
- L234 _public prototype_ `FSchemaElement CreateEncoding(const FSchemaEncodingParameters Parameters, const FName Tag = NAME_None);`
- L236 _public prototype_ `FSchemaContinuousParameters GetContinuous(const FSchemaElement Element) const;`
- L237 _public prototype_ `FSchemaDiscreteExclusiveParameters GetDiscreteExclusive(const FSchemaElement Element) const;`
- L238 _public prototype_ `FSchemaDiscreteInclusiveParameters GetDiscreteInclusive(const FSchemaElement Element) const;`
- L239 _public prototype_ `FSchemaNamedDiscreteExclusiveParameters GetNamedDiscreteExclusive(const FSchemaElement Element) const;`
- L240 _public prototype_ `FSchemaNamedDiscreteInclusiveParameters GetNamedDiscreteInclusive(const FSchemaElement Element) const;`
- L241 _public prototype_ `FSchemaAndParameters GetAnd(const FSchemaElement Element) const;`
- L242 _public prototype_ `FSchemaOrExclusiveParameters GetOrExclusive(const FSchemaElement Element) const;`
- L243 _public prototype_ `FSchemaOrInclusiveParameters GetOrInclusive(const FSchemaElement Element) const;`
- L244 _public prototype_ `FSchemaArrayParameters GetArray(const FSchemaElement Element) const;`
- L245 _public prototype_ `FSchemaEncodingParameters GetEncoding(const FSchemaElement Element) const;`
- L248 _public prototype_ `bool IsValid(const FSchemaElement Element) const;` — Checks if the given element is valid
- L251 _public prototype_ `EType GetType(const FSchemaElement Element) const;` — Gets the type of the given element
- L254 _public prototype_ `FName GetTag(const FSchemaElement Element) const;` — Gets the tag of the given element
- L257 _public prototype_ `int32 GetEncodedVectorSize(const FSchemaElement Element) const;` — Get the encoded vector size of the given element
- L260 _public prototype_ `int32 GetActionVectorSize(const FSchemaElement Element) const;` — Get the action vector size of the given element
- L263 _public prototype_ `int32 GetActionDistributionVectorSize(const FSchemaElement Element) const;` — Get the action distribution vector size of the given element
- L266 _public prototype_ `int32 GetActionModifierVectorSize(const FSchemaElement Element) const;` — Get the action modifier vector size of the given element
- L269 _public prototype_ `void SetGeneration(const uint32 InGeneration);` — Set the current generation
- L272 _public prototype_ `uint32 GetGeneration() const;` — Get the current generation
- L275 _public prototype_ `bool IsEmpty() const;` — Checks if the given schema is empty of elements.
- L278 _public prototype_ `void Empty();` — Empty all internal buffers of elements. This invalidates all existing elements.
- L281 _public prototype_ `void Reset();` — Reset all internal buffers (without freeing memory). This invalidates all existing elements.
- L284 _public prototype_ `bool Serialize(FArchive& Ar);` — Serializes an action schema. Returns false if serialization fails.
- L355 _private member_ `uint32 Generation = 0;`
- L358 _private member_ `TArray<EType> Types;` — These have entries for each Schema Element
- L359 _private member_ `TArray<FName> Tags;`
- L360 _private member_ `TArray<int32> EncodedVectorSizes;`
- L361 _private member_ `TArray<int32> ActionVectorSizes;`
- L362 _private member_ `TArray<int32> ActionDistributionVectorSizes;`
- L363 _private member_ `TArray<int32> ActionModifierVectorSizes;`
- L364 _private member_ `TArray<int32> TypeDataIndices;`
- L367 _private member_ `TArray<FContinuousData> ContinuousData;` — These are indexed based on the type and the index found in TypeDataIndices
- L368 _private member_ `TArray<FDiscreteExclusiveData> DiscreteExclusiveData;`
- L369 _private member_ `TArray<FDiscreteInclusiveData> DiscreteInclusiveData;`
- L370 _private member_ `TArray<FNamedDiscreteExclusiveData> NamedDiscreteExclusiveData;`
- L371 _private member_ `TArray<FNamedDiscreteInclusiveData> NamedDiscreteInclusiveData;`
- L372 _private member_ `TArray<FAndData> AndData;`
- L373 _private member_ `TArray<FOrExclusiveData> OrExclusiveData;`
- L374 _private member_ `TArray<FOrInclusiveData> OrInclusiveData;`
- L375 _private member_ `TArray<FArrayData> ArrayData;`
- L376 _private member_ `TArray<FEncodingData> EncodingData;`
- L379 _private member_ `TArray<FName> SubElementNames;` — This is an array of all the SubElements and their names, referenced by other elements
- L380 _private member_ `TArray<FSchemaElement> SubElementObjects;`
- L383 _private member_ `TArray<float> PriorProbabilities;` — This is an array of all the prior probabilities, referenced by other elements.
- L386 _private member_ `TArray<float> NormalizationScales;` — These are arrays for normalization values, referenced by continuous and flow matching elements.
- L387 _private member_ `TArray<float> NormalizationOffsets;`

#### struct `UE::Learning::Action::FSchema::FContinuousData`  
`struct FContinuousData`  
_L288-293_
- L290 _public member_ `int32 Num = INDEX_NONE;`
- L291 _public member_ `int32 NormalizationIndexOffset = INDEX_NONE;`
- L292 _public member_ `ENormalization NormalizationOption = ENormalization::Manual;`

#### struct `UE::Learning::Action::FSchema::FDiscreteExclusiveData`  
`struct FDiscreteExclusiveData`  
_L295-299_
- L297 _public member_ `int32 Num = INDEX_NONE;`
- L298 _public member_ `int32 PriorProbabilitiesOffset = INDEX_NONE;`

#### struct `UE::Learning::Action::FSchema::FDiscreteInclusiveData`  
`struct FDiscreteInclusiveData`  
_L301-305_
- L303 _public member_ `int32 Num = INDEX_NONE;`
- L304 _public member_ `int32 PriorProbabilitiesOffset = INDEX_NONE;`

#### struct `UE::Learning::Action::FSchema::FNamedDiscreteExclusiveData`  
`struct FNamedDiscreteExclusiveData`  
_L307-312_
- L309 _public member_ `int32 Num = INDEX_NONE;`
- L310 _public member_ `int32 PriorProbabilitiesOffset = INDEX_NONE;`
- L311 _public member_ `int32 ElementsOffset = INDEX_NONE;`

#### struct `UE::Learning::Action::FSchema::FNamedDiscreteInclusiveData`  
`struct FNamedDiscreteInclusiveData`  
_L314-319_
- L316 _public member_ `int32 Num = INDEX_NONE;`
- L317 _public member_ `int32 PriorProbabilitiesOffset = INDEX_NONE;`
- L318 _public member_ `int32 ElementsOffset = INDEX_NONE;`

#### struct `UE::Learning::Action::FSchema::FAndData`  
`struct FAndData`  
_L321-325_
- L323 _public member_ `int32 Num = INDEX_NONE;`
- L324 _public member_ `int32 ElementsOffset = INDEX_NONE;`

#### struct `UE::Learning::Action::FSchema::FOrExclusiveData`  
`struct FOrExclusiveData`  
_L327-332_
- L329 _public member_ `int32 Num = INDEX_NONE;`
- L330 _public member_ `int32 ElementsOffset = INDEX_NONE;`
- L331 _public member_ `int32 PriorProbabilitiesOffset = INDEX_NONE;`

#### struct `UE::Learning::Action::FSchema::FOrInclusiveData`  
`struct FOrInclusiveData`  
_L334-339_
- L336 _public member_ `int32 Num = INDEX_NONE;`
- L337 _public member_ `int32 ElementsOffset = INDEX_NONE;`
- L338 _public member_ `int32 PriorProbabilitiesOffset = INDEX_NONE;`

#### struct `UE::Learning::Action::FSchema::FArrayData`  
`struct FArrayData`  
_L341-345_
- L343 _public member_ `int32 Num = INDEX_NONE;`
- L344 _public member_ `int32 ElementIndex = INDEX_NONE;`

#### struct `UE::Learning::Action::FSchema::FEncodingData`  
`struct FEncodingData`  
_L347-353_
- L349 _public member_ `int32 EncodingSize = INDEX_NONE;`
- L350 _public member_ `int32 ElementIndex = INDEX_NONE;`
- L351 _public member_ `int32 LayerNum = INDEX_NONE;`
- L352 _public member_ `EEncodingActivationFunction ActivationFunction = EEncodingActivationFunction::ELU;`

#### struct `UE::Learning::Action::FObjectElement`  
`struct FObjectElement`  
_L396-396_
- desc: Action Object Element A single element in the action object representing part of an action. Internally this consists of a index used by the object to look up the associated action data and a generation id which can be used to check when this index is no longer valid.
- L396 _public member_ `struct FObjectElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Action Object Element A single element in the action object representing part of an action. Internally this consists of a index used by the object to look up the associated action data and a generation id which can be used to check when this index is no longer valid.
- L396 _public member_ `struct FObjectElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Action Object Element A single element in the action object representing part of an action. Internally this consists of a index used by the object to look up the associated action data and a generation id which can be used to check when this index is no longer valid.

#### struct `UE::Learning::Action::FObjectContinuousParameters`  
`struct FObjectContinuousParameters`  
_L398-402_
- L401 _public member_ `TArrayView<const float> Values;` — Continuous action values

#### struct `UE::Learning::Action::FObjectDiscreteExclusiveParameters`  
`struct FObjectDiscreteExclusiveParameters`  
_L404-408_
- L407 _public member_ `int32 DiscreteIndex = INDEX_NONE;` — Exclusive discrete action index

#### struct `UE::Learning::Action::FObjectDiscreteInclusiveParameters`  
`struct FObjectDiscreteInclusiveParameters`  
_L410-414_
- L413 _public member_ `TArrayView<const int32> DiscreteIndices;` — Inclusive discrete action indices

#### struct `UE::Learning::Action::FObjectNamedDiscreteExclusiveParameters`  
`struct FObjectNamedDiscreteExclusiveParameters`  
_L416-420_
- L419 _public member_ `FName ElementName = NAME_None;` — Named Exclusive discrete action name

#### struct `UE::Learning::Action::FObjectNamedDiscreteInclusiveParameters`  
`struct FObjectNamedDiscreteInclusiveParameters`  
_L422-426_
- L425 _public member_ `TArrayView<const FName> ElementNames;` — Named Inclusive discrete action name

#### struct `UE::Learning::Action::FObjectAndParameters`  
`struct FObjectAndParameters`  
_L428-435_
- L431 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sub-actions.
- L434 _public member_ `TArrayView<const FObjectElement> Elements;` — The associated sub-elements.

#### struct `UE::Learning::Action::FObjectOrExclusiveParameters`  
`struct FObjectOrExclusiveParameters`  
_L437-444_
- L440 _public member_ `FName ElementName;` — Name of the chosen sub-action.
- L443 _public member_ `FObjectElement Element;` — The associated chosen sub-element.

#### struct `UE::Learning::Action::FObjectOrInclusiveParameters`  
`struct FObjectOrInclusiveParameters`  
_L446-453_
- L449 _public member_ `TArrayView<const FName> ElementNames;` — Names of the chosen sub-actions.
- L452 _public member_ `TArrayView<const FObjectElement> Elements;` — The associated chosen sub-elements.

#### struct `UE::Learning::Action::FObjectArrayParameters`  
`struct FObjectArrayParameters`  
_L455-459_
- L458 _public member_ `TArrayView<const FObjectElement> Elements;` — Array of sub-elements.

#### struct `UE::Learning::Action::FObjectEncodingParameters`  
`struct FObjectEncodingParameters`  
_L461-465_
- L464 _public member_ `FObjectElement Element;` — Encoded sub-element.

#### struct `UE::Learning::Action::FObjectFlowMatchingParameters`  
`struct FObjectFlowMatchingParameters`  
_L467-471_
- L470 _public member_ `TArrayView<const float> Values;` — Flow matching float action values

#### struct `UE::Learning::Action::FObject`  
`struct FObject`  
_L480-551_
- desc: Action Object This object allows you to construct or get data from an instance of an action you might have generated from a policy. Internally this object contains a pool of individual elements. This allows them to be constructed performantly and in a cache efficient way. This object is therefore required to access any data about the individual action elements that are created.
- L482 _public prototype_ `FObjectElement CreateNull(const FName Tag = NAME_None);`
- L483 _public prototype_ `FObjectElement CreateContinuous(const FObjectContinuousParameters Parameters, const FName Tag = NAME_None);`
- L484 _public prototype_ `FObjectElement CreateDiscreteExclusive(const FObjectDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L485 _public prototype_ `FObjectElement CreateDiscreteInclusive(const FObjectDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L486 _public prototype_ `FObjectElement CreateNamedDiscreteExclusive(const FObjectNamedDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L487 _public prototype_ `FObjectElement CreateNamedDiscreteInclusive(const FObjectNamedDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L488 _public prototype_ `FObjectElement CreateAnd(const FObjectAndParameters Parameters, const FName Tag = NAME_None);`
- L489 _public prototype_ `FObjectElement CreateOrExclusive(const FObjectOrExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L490 _public prototype_ `FObjectElement CreateOrInclusive(const FObjectOrInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L491 _public prototype_ `FObjectElement CreateArray(const FObjectArrayParameters Parameters, const FName Tag = NAME_None);`
- L492 _public prototype_ `FObjectElement CreateEncoding(const FObjectEncodingParameters Parameters, const FName Tag = NAME_None);`
- L493 _public prototype_ `FObjectElement CreateFlowMatching(const FObjectFlowMatchingParameters Parameters, const FName Tag = NAME_None);`
- L495 _public prototype_ `FObjectContinuousParameters GetContinuous(const FObjectElement Element) const;`
- L496 _public prototype_ `FObjectDiscreteExclusiveParameters GetDiscreteExclusive(const FObjectElement Element) const;`
- L497 _public prototype_ `FObjectDiscreteInclusiveParameters GetDiscreteInclusive(const FObjectElement Element) const;`
- L498 _public prototype_ `FObjectNamedDiscreteExclusiveParameters GetNamedDiscreteExclusive(const FObjectElement Element) const;`
- L499 _public prototype_ `FObjectNamedDiscreteInclusiveParameters GetNamedDiscreteInclusive(const FObjectElement Element) const;`
- L500 _public prototype_ `FObjectAndParameters GetAnd(const FObjectElement Element) const;`
- L501 _public prototype_ `FObjectOrExclusiveParameters GetOrExclusive(const FObjectElement Element) const;`
- L502 _public prototype_ `FObjectOrInclusiveParameters GetOrInclusive(const FObjectElement Element) const;`
- L503 _public prototype_ `FObjectArrayParameters GetArray(const FObjectElement Element) const;`
- L504 _public prototype_ `FObjectEncodingParameters GetEncoding(const FObjectElement Element) const;`
- L505 _public prototype_ `FObjectFlowMatchingParameters GetFlowMatching(const FObjectElement Element) const;`
- L508 _public prototype_ `bool IsValid(const FObjectElement Element) const;` — Checks if the given element is valid
- L511 _public prototype_ `EType GetType(const FObjectElement Element) const;` — Gets the type of the given element
- L514 _public prototype_ `FName GetTag(const FObjectElement Element) const;` — Gets the tag of the given element
- L517 _public prototype_ `void SetGeneration(const uint32 InGeneration);` — Set the current generation
- L520 _public prototype_ `uint32 GetGeneration() const;` — Get the current generation
- L523 _public prototype_ `bool IsEmpty() const;` — Checks if the given object is empty of elements.
- L526 _public prototype_ `void Empty();` — Empty all internal buffers of elements. This invalidates all existing elements.
- L529 _public prototype_ `void Reset();` — Reset all internal buffers (without freeing memory). This invalidates all existing elements.
- L532 _public prototype_ `bool Serialize(FArchive& Ar);` — Serializes an action object. Returns false if serialization fails.
- L536 _private member_ `uint32 Generation = 0;`
- L538 _private member_ `TArray<EType> Types;`
- L539 _private member_ `TArray<FName> Tags;`
- L540 _private member_ `TArray<int32> ContinuousDataOffsets;`
- L541 _private member_ `TArray<int32> ContinuousDataNums;`
- L542 _private member_ `TArray<int32> DiscreteDataOffsets;`
- L543 _private member_ `TArray<int32> DiscreteDataNums;`
- L544 _private member_ `TArray<int32> ElementDataOffsets;`
- L545 _private member_ `TArray<int32> ElementDataNums;`
- L547 _private member_ `TArray<float> ContinuousValues;`
- L548 _private member_ `TArray<int32> DiscreteValues;`
- L549 _private member_ `TArray<FName> SubElementNames;`
- L550 _private member_ `TArray<FObjectElement> SubElementObjects;`

#### struct `UE::Learning::Action::FModifierElement`  
`struct FModifierElement`  
_L561-561_
- desc: Action Modifier Element A single element representing a modification to an action performed during sampling (such as masking). Internally this consists of a index used by the object to look up the associated action modification data and a generation id which can be used to check when this index is no longer valid.
- L561 _public member_ `struct FModifierElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Action Modifier Element A single element representing a modification to an action performed during sampling (such as masking). Internally this consists of a index used by the object to look up the associated action modification data and a generation id which can be used to check when this index is no longer valid.
- L561 _public member_ `struct FModifierElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Action Modifier Element A single element representing a modification to an action performed during sampling (such as masking). Internally this consists of a index used by the object to look up the associated action modification data and a generation id which can be used to check when this index is no longer valid.

#### struct `UE::Learning::Action::FModifierContinuousParameters`  
`struct FModifierContinuousParameters`  
_L563-570_
- L566 _public member_ `TArrayView<const bool> Masked;` — Indicates which dimensions are masked
- L569 _public member_ `TArrayView<const float> MaskedValues;` — Values used to replace masked dimensions

#### struct `UE::Learning::Action::FModifierDiscreteExclusiveParameters`  
`struct FModifierDiscreteExclusiveParameters`  
_L572-576_
- L575 _public member_ `TArrayView<const int32> MaskedIndices;` — Disallowed indices

#### struct `UE::Learning::Action::FModifierDiscreteInclusiveParameters`  
`struct FModifierDiscreteInclusiveParameters`  
_L578-582_
- L581 _public member_ `TArrayView<const int32> MaskedIndices;` — Disallowed indices

#### struct `UE::Learning::Action::FModifierNamedDiscreteExclusiveParameters`  
`struct FModifierNamedDiscreteExclusiveParameters`  
_L584-588_
- L587 _public member_ `TArrayView<const FName> MaskedElementNames;` — Disallowed actions

#### struct `UE::Learning::Action::FModifierNamedDiscreteInclusiveParameters`  
`struct FModifierNamedDiscreteInclusiveParameters`  
_L590-594_
- L593 _public member_ `TArrayView<const FName> MaskedElementNames;` — Disallowed actions

#### struct `UE::Learning::Action::FModifierAndParameters`  
`struct FModifierAndParameters`  
_L596-603_
- L599 _public member_ `TArrayView<const FName> ElementNames;` — Names of the modified sub-actions.
- L602 _public member_ `TArrayView<const FModifierElement> Elements;` — The modifiers of the associated sub-elements.

#### struct `UE::Learning::Action::FModifierOrExclusiveParameters`  
`struct FModifierOrExclusiveParameters`  
_L605-615_
- L608 _public member_ `TArrayView<const FName> ElementNames;` — Names of the modified sub-action.
- L611 _public member_ `TArrayView<const FModifierElement> Elements;` — The modifiers of the associated sub-element.
- L614 _public member_ `TArrayView<const FName> MaskedElements;` — Disallowed sub-elements

#### struct `UE::Learning::Action::FModifierOrInclusiveParameters`  
`struct FModifierOrInclusiveParameters`  
_L617-627_
- L620 _public member_ `TArrayView<const FName> ElementNames;` — Names of the modified sub-actions.
- L623 _public member_ `TArrayView<const FModifierElement> Elements;` — The modifiers of the associated sub-elements.
- L626 _public member_ `TArrayView<const FName> MaskedElements;` — Disallowed sub-elements

#### struct `UE::Learning::Action::FModifierArrayParameters`  
`struct FModifierArrayParameters`  
_L629-633_
- L632 _public member_ `TArrayView<const FModifierElement> Elements;` — Array of sub-element modifiers.

#### struct `UE::Learning::Action::FModifierEncodingParameters`  
`struct FModifierEncodingParameters`  
_L635-639_
- L638 _public member_ `FModifierElement Element;` — Encoded sub-element modifier.

#### struct `UE::Learning::Action::FModifier`  
`struct FModifier`  
_L648-721_
- desc: Action Modifier This object allows you to describe modifications you want to apply to actions during the sampling stage. Internally this object contains a pool of individual elements. This allows them to be constructed performantly and in a cache efficient way. This object is therefore required to access any data about the individual action modifier elements that are created.
- L650 _public prototype_ `FModifierElement CreateNull(const FName Tag = NAME_None);`
- L651 _public prototype_ `FModifierElement CreateContinuous(const FModifierContinuousParameters Parameters, const FName Tag = NAME_None);`
- L652 _public prototype_ `FModifierElement CreateDiscreteExclusive(const FModifierDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L653 _public prototype_ `FModifierElement CreateDiscreteInclusive(const FModifierDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L654 _public prototype_ `FModifierElement CreateNamedDiscreteExclusive(const FModifierNamedDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L655 _public prototype_ `FModifierElement CreateNamedDiscreteInclusive(const FModifierNamedDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L656 _public prototype_ `FModifierElement CreateAnd(const FModifierAndParameters Parameters, const FName Tag = NAME_None);`
- L657 _public prototype_ `FModifierElement CreateOrExclusive(const FModifierOrExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L658 _public prototype_ `FModifierElement CreateOrInclusive(const FModifierOrInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L659 _public prototype_ `FModifierElement CreateArray(const FModifierArrayParameters Parameters, const FName Tag = NAME_None);`
- L660 _public prototype_ `FModifierElement CreateEncoding(const FModifierEncodingParameters Parameters, const FName Tag = NAME_None);`
- L662 _public prototype_ `FModifierContinuousParameters GetContinuous(const FModifierElement Element) const;`
- L663 _public prototype_ `FModifierDiscreteExclusiveParameters GetDiscreteExclusive(const FModifierElement Element) const;`
- L664 _public prototype_ `FModifierDiscreteInclusiveParameters GetDiscreteInclusive(const FModifierElement Element) const;`
- L665 _public prototype_ `FModifierNamedDiscreteExclusiveParameters GetNamedDiscreteExclusive(const FModifierElement Element) const;`
- L666 _public prototype_ `FModifierNamedDiscreteInclusiveParameters GetNamedDiscreteInclusive(const FModifierElement Element) const;`
- L667 _public prototype_ `FModifierAndParameters GetAnd(const FModifierElement Element) const;`
- L668 _public prototype_ `FModifierOrExclusiveParameters GetOrExclusive(const FModifierElement Element) const;`
- L669 _public prototype_ `FModifierOrInclusiveParameters GetOrInclusive(const FModifierElement Element) const;`
- L670 _public prototype_ `FModifierArrayParameters GetArray(const FModifierElement Element) const;`
- L671 _public prototype_ `FModifierEncodingParameters GetEncoding(const FModifierElement Element) const;`
- L674 _public prototype_ `bool IsValid(const FModifierElement Element) const;` — Checks if the given element is valid
- L677 _public prototype_ `EType GetType(const FModifierElement Element) const;` — Gets the type of the given element
- L680 _public prototype_ `FName GetTag(const FModifierElement Element) const;` — Gets the tag of the given element
- L683 _public prototype_ `void SetGeneration(const uint32 InGeneration);` — Set the current generation
- L686 _public prototype_ `uint32 GetGeneration() const;` — Get the current generation
- L689 _public prototype_ `bool IsEmpty() const;` — Checks if the given object is empty of elements.
- L692 _public prototype_ `void Empty();` — Empty all internal buffers of elements. This invalidates all existing elements.
- L695 _public prototype_ `void Reset();` — Reset all internal buffers (without freeing memory). This invalidates all existing elements.
- L698 _public prototype_ `bool Serialize(FArchive& Ar);` — Serializes an action modifier object. Returns false if serialization fails.
- L702 _private member_ `uint32 Generation = 0;`
- L704 _private member_ `TArray<EType> Types;`
- L705 _private member_ `TArray<FName> Tags;`
- L706 _private member_ `TArray<int32> ContinuousDataOffsets;`
- L707 _private member_ `TArray<int32> ContinuousDataNums;`
- L708 _private member_ `TArray<int32> DiscreteDataOffsets;`
- L709 _private member_ `TArray<int32> DiscreteDataNums;`
- L710 _private member_ `TArray<int32> ElementDataOffsets;`
- L711 _private member_ `TArray<int32> ElementDataNums;`
- L712 _private member_ `TArray<int32> MaskedDataOffsets;`
- L713 _private member_ `TArray<int32> MaskedDataNums;`
- L715 _private member_ `TArray<bool> ContinuousMaskeds;`
- L716 _private member_ `TArray<float> ContinuousMaskedValues;`
- L717 _private member_ `TArray<int32> DiscreteValues;`
- L718 _private member_ `TArray<FName> SubElementNames;`
- L719 _private member_ `TArray<FModifierElement> SubElementModifiers;`
- L720 _private member_ `TArray<FName> MaskedElementNames;`

#### enum `UE::Learning::Action::EWeightInitialization`  
`enum class EWeightInitialization : uint8`  
_L753-757_
- desc: Network weight initialization type
- L755 _public enumerator_ `KaimingGaussian = 0`
- L756 _public enumerator_ `KaimingUniform = 1`

#### struct `UE::Learning::Action::FNetworkSettings`  
`struct FNetworkSettings`  
_L762-769_
- desc: Settings for building a network from a schema.
- L765 _public member_ `bool bUseCompressedLinearLayers = false;` — If to use compressed linear layers. This reduces the memory usage by half at the cost of some small impact on quality and evaluation speed.
- L768 _public member_ `EWeightInitialization WeightInitialization = EWeightInitialization::KaimingGaussian;` — Which weight initialization to use.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNING_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNE` (scope `UE`)
- L11 _namespace_ `namespace RuntimeBasic` (scope `UE::NNE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Learning` (scope `UE`)
- L17 _namespace_ `namespace Action` (scope `UE::Learning`)
- L67 _function_ `static inline FString GetNormalizationOptionAsString(const ENormalization NormalizationOption)` (scope `UE::Learning::Action`)
- L188 _function_ `static inline FString GetEncodingActivationAsString(const EEncodingActivationFunction ActivationFunction)` (scope `UE::Learning::Action`)
- L732 _prototype_ `int32 GetSchemaObjectsCompatibilityHash( const FSchema& Schema, const FSchemaElement SchemaElement, const int32 Salt = 0x49710e77);` (scope `UE::Learning::Action`) — Gets a hash value representing object compatibility between schemas i.e. if objects from one schema can be used by objects expecting another schema. This is not a cryptographic hash, and so `AreSchemaObjectsCompatible` should still be used as the ultimate source of truth. This function returns an int32 so that it can be used in blueprints. @param Schema					Action Schema @param SchemaElement				Action Schema Element @param Salt						Hash salt
- L746 _prototype_ `bool AreSchemaObjectsCompatible( const FSchema& SchemaA, const FSchemaElement SchemaElementA, const FSchema& SchemaB, const FSchemaElement SchemaElementB);` (scope `UE::Learning::Action`) — Test if two schemas are compatible i.e. if objects from one schema can be used by objects expecting another schema. @param SchemaA					First Schema @param SchemaElementA			First Schema Element @param SchemaB					Second Schema @param SchemaElementB			Second Schema Element @returns							true when the schemas are compatible
- L781 _prototype_ `void MakeDecoderNetworkModelBuilderElementFromSchema( NNE::RuntimeBasic::FModelBuilderElement& OutElement, NNE::RuntimeBasic::FModelBuilder& Builder, const FSchema& Schema, const FSchemaElement SchemaElement, const FNetworkSettings& NetworkSettings = FNetworkSettings());` (scope `UE::Learning::Action`) — Make a NNE::RuntimeBasic::FModelBuilderElement for the given Schema. This can be used if you want to plug the Decoder generated by this schema as a part of a larger model you are making with a NNE::RuntimeBasic::FModelBuilder. @param OutElement				Output Builder Element @param Builder					Model Builder @param Schema					Action Schema @param SchemaElement				Action Schema Element @param NetworkSettings			Network Generation Settings
- L800 _prototype_ `void GenerateDecoderNetworkFileDataFromSchema( TArray<uint8>& OutFileData, uint32& OutInputSize, uint32& OutOutputSize, const FSchema& Schema, const FSchemaElement SchemaElement, const FNetworkSettings& NetworkSettings = FNetworkSettings(), const uint32 Seed = 0x05dbd1f5);` (scope `UE::Learning::Action`) — Generate FileData for a Neural Network that can act as a Decoder for the given schema. This network will take as input a vector of size EncodedActionSize and produce a vector of size ActionDistributionVectorSize. @param OutFileData				Output File Data to write to @param OutInputSize				Size of the vector this network takes as input @param OutOutputSize				Size of the vector this network takes as output @param Schema					Action Schema @param SchemaElement				Action Schema Element @param NetworkSettings			Network Generation Settings @param Seed						The random seed used in initializing the network weights
- L820 _prototype_ `void SampleVectorFromDistributionVector( uint32& InOutRandomState, TLearningArrayView<1, float> OutActionVector, const TLearningArrayView<1, const float> ActionDistributionVector, const TLearningArrayView<1, const float> ActionModifierVector, const FSchema& Schema, const FSchemaElement SchemaElement, const float ActionNoiseScale = 1.0f);` (scope `UE::Learning::Action`) — Sample an action vector from a vector representing the action distribution. @param InOutRandomState			Random State/Seed to use when sampling the action vector @param OutActionVector			Output action vector @param ActionDistributionVector	Input Action Distribution vector @param ActionModifierVector		Input Action Modifier vector @param Schema					Action Schema @param SchemaElement				Action Schema Element @param ActionNoiseScale			Scale factor for the noise. Set this to zero to always choose the mean (expected) action.
- L838 _prototype_ `void SetVectorFromObject( TLearningArrayView<1, float> OutActionVector, const FSchema& Schema, const FSchemaElement SchemaElement, const FObject& Object, const FObjectElement ObjectElement);` (scope `UE::Learning::Action`) — Convert an action object into an action vector. @param OutActionVector			Output action vector @param Schema					Action Schema @param SchemaElement				Action Schema Element @param Object					Action Object @param ObjectElement				Action Object Element
- L854 _prototype_ `void GetObjectFromVector( FObject& OutObject, FObjectElement& OutObjectElement, const FSchema& Schema, const FSchemaElement SchemaElement, const TLearningArrayView<1, const float> ActionVector);` (scope `UE::Learning::Action`) — Convert an action vector into an action object @param OutObject					Output Action Object @param OutObjectElement			Output Action Object Element @param Schema					Action Schema @param SchemaElement				Action Schema Element @param ActionVector				Input Action vector
- L870 _prototype_ `void SetVectorFromModifier( TLearningArrayView<1, float> OutActionModifierVector, const FSchema& Schema, const FSchemaElement SchemaElement, const FModifier& Modifier, const FModifierElement ModifierElement);` (scope `UE::Learning::Action`) — Convert an action modifier into an action modifier vector. @param OutActionModifierVector	Output action modifier vector @param Schema					Action Schema @param SchemaElement				Action Schema Element @param Modifier					Action Modifier @param ModifierElement			Action Modifier Element
- L886 _prototype_ `void GetModifierFromVector( FModifier& OutModifier, FModifierElement& OutModifierElement, const FSchema& Schema, const FSchemaElement SchemaElement, const TLearningArrayView<1, const float> ActionModifierVector);` (scope `UE::Learning::Action`) — Convert an action modifier vector into an action modifier @param OutModifier				Output Action Modifier @param OutModifierElement		Output Action Modifier Element @param Schema					Action Schema @param SchemaElement				Action Schema Element @param ActionModifierVector		Input Action Modifier vector
- L894 _prototype_ `FArchive& operator<<(FArchive& Ar, UE::Learning::Action::FSchemaElement& SchemaElement);`
- L895 _prototype_ `FArchive& operator<<(FArchive& Ar, UE::Learning::Action::FObjectElement& ObjectElement);`
- L896 _prototype_ `FArchive& operator<<(FArchive& Ar, UE::Learning::Action::FModifierElement& ModifierElement);`
- L897 _prototype_ `bool operator==(const UE::Learning::Action::FSchemaElement& Lhs, const UE::Learning::Action::FSchemaElement& Rhs);`
- L898 _prototype_ `bool operator==(const UE::Learning::Action::FObjectElement& Lhs, const UE::Learning::Action::FObjectElement& Rhs);`
- L899 _prototype_ `bool operator==(const UE::Learning::Action::FModifierElement& Lhs, const UE::Learning::Action::FModifierElement& Rhs);`
- L900 _prototype_ `uint32 GetTypeHash(const UE::Learning::Action::FSchemaElement& SchemaElement);`
- L901 _prototype_ `uint32 GetTypeHash(const UE::Learning::Action::FObjectElement& ObjectElement);`
- L902 _prototype_ `uint32 GetTypeHash(const UE::Learning::Action::FModifierElement& ModifierElement);`

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningAdamOptimizer.h` (Public)


#### struct `UE::Learning::FAdamOptimizerSettings`  
`struct FAdamOptimizerSettings`  
_L11-26_
- L16 _public member_ `float FiniteDifferenceStd = 0.3f;` — The size of the std for finite differencing. This may need to be increased if the optimizer does not appear to be doing anything
- L19 _public member_ `float LearningRate = 0.1f;` — Update learning rate. Larger values may speed up convergence at the cost of instability.
- L22 _public member_ `float Beta1 = 0.9f;` — First moment momentum ratio. Reduce if seeing large swings in the loss
- L25 _public member_ `float Beta2 = 0.999f;` — Second moment momentum ratio. Reduce if seeing large swings in the loss

#### struct `UE::Learning::FAdamOptimizer`  
`struct FAdamOptimizer : public IOptimizer`  
_L34-65_
- inherits: `IOptimizer`
- desc: Adam Optimizer Estimates gradient via finite differencing and does gradient descent. Roughly based on https://arxiv.org/abs/1910.06513
- L36 _public prototype_ `FAdamOptimizer(const uint32 Seed, const FAdamOptimizerSettings& InSettings = FAdamOptimizerSettings());`
- L38 _public prototype_ `virtual void Resize(const int32 SampleNum, const int32 DimensionsNum) override final;`
- L40 _public prototype_ `virtual void Reset( TLearningArrayView<2, float> OutSamples, const TLearningArrayView<1, const float> InitialGuess) override final;`
- L44 _public prototype_ `virtual void Update( TLearningArrayView<2, float> InOutSamples, const TLearningArrayView<1, const float> Losses, const ELogSetting LogSettings = ELogSetting::Normal) override final;`
- L51 _private prototype_ `void Sample(TLearningArrayView<2, float> OutSamples);`
- L53 _private member_ `uint32 Seed = 0;`
- L54 _private member_ `FAdamOptimizerSettings Settings;`
- L56 _private member_ `TLearningArray<1, int32> Iterations;`
- L57 _private member_ `TLearningArray<1, float> Estimate;`
- L58 _private member_ `TLearningArray<1, float> Gradient;`
- L60 _private member_ `TLearningArray<1, float> M0;`
- L61 _private member_ `TLearningArray<1, float> M1;`
- L62 _private member_ `TLearningArray<1, float> M1HatMax;`
- L64 _private member_ `TLearningArray<2, float> GaussianSamples;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEARNING_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningArray.h` (Public)


#### struct `UE::Learning::FIndexSetIterator`  
`struct FIndexSetIterator`  
_L41-54_
- desc: Iterator for FIndexSet (see below)
- L43 _public function_ `FIndexSetIterator(const int32* InPtr) : bUseIndex(false), Index(0), Ptr(InPtr)`
- L44 _public function_ `FIndexSetIterator(int32 InIndex) : bUseIndex(true), Index(InIndex), Ptr(nullptr)`
- L46 _public function_ `bool operator!=(const FIndexSetIterator& Rhs) const`
- L47 _public function_ `FIndexSetIterator& operator++()`
- L48 _public function_ `int32 operator*() const`
- L51 _private member_ `const bool bUseIndex = true;`
- L52 _private member_ `int32 Index = 0;`
- L53 _private member_ `const int32* Ptr = nullptr;`

#### struct `UE::Learning::FIndexSet`  
`struct FIndexSet`  
_L72-197_
- desc: FIndexSet represents a set of indices - more specifically, either a slice of indices, or an ArrayView of int32 which acts as the set of indices. This type is generally used when we have allocated arrays of data but only need to iterate over or update a subset. For example, if we allocate data for 100 instances, but only 10 of those instances are active we can use an FIndexSet to indicate which ones. Having this type act as either a slice or array of int32 lets us write code once, but still allows the compiler to potentially generate both code paths (or we can write both paths manually, using ispc to be more efficient when we have a slice and don't require random reads/writes). We can also attempt to automatically convert index sets which contain consecutive indices from arrays of int32 to slices using the `TryMakeSlice` function for more efficient processing.
- L74 _public prototype_ `FIndexSet() = default;`
- L75 _public function_ `FIndexSet(const int32 InSingleIndex) : SliceStart(InSingleIndex), SliceNum(1)`
- L76 _public function_ `FIndexSet(const int32 InSliceStart, const int32 InSliceNum) : SliceStart(InSliceStart), SliceNum(InSliceNum)`
- L77 _public function_ `FIndexSet(const TArrayView<const int32> InIndices) : Indices(InIndices)`
- L78 _public function_ `FIndexSet(const TLearningArrayView<1, const int32> InIndices) : Indices(InIndices)`
- L79 _public function_ `FIndexSet(const TArrayView<int32> InIndices) : Indices(InIndices)`
- L80 _public function_ `FIndexSet(const TLearningArrayView<1, int32> InIndices) : Indices(InIndices)`
- L81 _public function_ `FIndexSet(std::initializer_list<int32> InIndices) : Indices(InIndices)`
- L84 _public function_ `template<typename InAllocatorType> FIndexSet(const TArray<int32, InAllocatorType>& InIndices) : Indices(InIndices)`
- L87 _public function_ `template<typename InAllocatorType> FIndexSet(const TLearningArray<1, int32, InAllocatorType>& InIndices) : Indices(InIndices)`
- L89 _public function_ `FIndexSet& operator=(const int32 InSingleIndex)`
- L90 _public function_ `FIndexSet& operator=(const TArrayView<const int32> InIndices)`
- L91 _public function_ `FIndexSet& operator=(TLearningArrayView<1, const int32> InIndices)`
- L94 _public function_ `template<typename InAllocatorType> FIndexSet& operator=(const TArray<int32, InAllocatorType>& InIndices)`
- L97 _public function_ `template<typename InAllocatorType> FIndexSet& operator=(const TLearningArray<1, int32, InAllocatorType>& InIndices)`
- L99 _public function_ `TArray<int32> ToArray() const`
- L121 _public prototype_ `bool TryMakeSlice();` — Attempts to convert this IndexSet from a view of indices into a slice for more efficient processing. This works by finding the minimum and maximum elements in the array and comparing the range of this min and max to the number of elements. When indices are consecutive `Max - Min + 1 == Num`. Warning: this algorithm works on the assumption that there are no duplicate indices in the view. If there are duplicate indices in your set this will not give the correct result. @returns true if conversion to a slice is successful
- L123 _public function_ `inline int32 operator[](const int32 Index) const`
- L128 _public function_ `inline int32 Num() const`
- L133 _public function_ `inline FIndexSet Slice(const int32 InStart, const int32 InNum) const`
- L145 _public function_ `inline bool Contains(const int32 Index) const`
- L150 _public function_ `inline int32 Find(const int32 Index) const`
- L174 _public function_ `inline FIndexSetIterator begin() const`
- L181 _public function_ `inline FIndexSetIterator end() const`
- L188 _public function_ `inline bool IsSlice() const`
- L189 _public function_ `inline int32 GetSliceStart() const`
- L190 _public function_ `inline int32 GetSliceNum() const`
- L191 _public function_ `inline TLearningArrayView<1, const int32> GetIndices() const`
- L195 _private member_ `int32 SliceStart = 0, SliceNum = 0;`
- L195 _private member_ `int32 SliceStart = 0, SliceNum = 0;`
- L196 _private member_ `TLearningArrayView<1, const int32> Indices;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LEARNING_API`
- L16 _macro_ `#define UE_LEARNING_ISPC INTEL_ISPC`
- L23 _typedef_ `template<uint32 DimNum> using TLearningArrayShape = TMultiArrayShape<DimNum>;`
- L26 _typedef_ `template<uint32 DimNum, typename ElementType> using TLearningArrayView = TMultiArrayView<DimNum, ElementType>;`
- L29 _typedef_ `template<uint32 DimNum, typename ElementType> using TLearningConstArrayView = TConstMultiArrayView<DimNum, ElementType>;`
- L32 _typedef_ `template<uint32 DimNum, typename ElementType, typename Allocator = FDefaultAllocator64> using TLearningArray = TMultiArray<DimNum, ElementType, Allocator>;`
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace Learning` (scope `UE`)
- L210 _prototype_ `void SlicedParallelFor(const int32 Num, const int32 MinSliceElementNum, const TFunctionRef<void(const int32 Start, const int32 Length)> Body);` (scope `UE::Learning`) — Similar to `ParallelFor` but instead of providing a single index to the callback it provides a slice for the callback to loop over. The advantage here is that it gives the compiler a chance of optimizing the loop code in the callback such as unrolling and auto-vectorizing. This is important when the number of items to loop over is large (e.g. ~1000) since otherwise this would produce an individual function call for every element in the loop. @param Num					Number of elements to iterate over @param MinSliceElementNum		Minimum number of elements to include in each call to Body @param Body					Callback taking start and stop index slice of Num
- L215 _function_ `static inline void SerializeToBytes(int64& InOutOffset, TLearningArrayView<1, uint8> Bytes, const uint8 InValue)` (scope `UE::Learning`) — Serialize an integer to bytes
- L225 _function_ `static inline void SerializeToBytes(int64& InOutOffset, TLearningArrayView<1, uint8> Bytes, const int32 InValue)` (scope `UE::Learning`) — Serialize an integer to bytes
- L235 _function_ `static inline void SerializeToBytes(int64& InOutOffset, TLearningArrayView<1, uint8> Bytes, const int64 InValue)` (scope `UE::Learning`) — Serialize an integer to bytes
- L245 _function_ `static inline void DeserializeFromBytes(int64& InOutOffset, TLearningArrayView<1, const uint8> Bytes, uint8& OutValue)` (scope `UE::Learning`) — Deserialize an integer from bytes
- L255 _function_ `static inline void DeserializeFromBytes(int64& InOutOffset, TLearningArrayView<1, const uint8> Bytes, int32& OutValue)` (scope `UE::Learning`) — Deserialize an integer from bytes
- L265 _function_ `static inline void DeserializeFromBytes(int64& InOutOffset, TLearningArrayView<1, const uint8> Bytes, int64& OutValue)` (scope `UE::Learning`) — Deserialize an integer from bytes
- L275 _function_ `static inline void DeserializeFromBytes(int64& InOutOffset, TLearningArrayView<1, const uint8> Bytes, uint64& OutValue)` (scope `UE::Learning`) — Deserialize an integer from bytes
- L288 _namespace_ `namespace Array` (scope `UE::Learning`)
- L294 _function_ `template<uint8 InDimNum> inline void CheckShapesEqual(const TLearningArrayShape<InDimNum>& Lhs, const TLearningArrayShape<InDimNum>& Rhs)` (scope `UE::Learning::Array`) — Check that two array shapes are equal.
- L307 _function_ `template<uint8 InDimNum, typename InElementType> inline void Check(const TLearningArrayView<InDimNum, InElementType> View)` (scope `UE::Learning::Array`) — Check that an array view does not contain any NaN, Inf, -Inf
- L321 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Check(const TLearningArray<InDimNum, InElementType, Allocator>& View)` (scope `UE::Learning::Array`) — Check that an array does not contain any NaN, Inf, -Inf
- L335 _function_ `template<uint8 InDimNum, typename InElementType> inline void Check(const TLearningArrayView<InDimNum, InElementType> View, const FIndexSet Indices)` (scope `UE::Learning::Array`) — Check that an array view does not contain any NaN, Inf, -Inf
- L359 _function_ `template<uint8 InDimNum, typename InElementType> inline void Check(const TLearningArray<InDimNum, InElementType>& View, const FIndexSet Indices)` (scope `UE::Learning::Array`) — Check that an array view does not contain any NaN, Inf, -Inf
- L381 _prototype_ `void FloatArrayZero32(float* Data, const int32 Num);` (scope `UE::Learning::Array`)
- L382 _prototype_ `void FloatArraySet32(float* Data, const int32 Num, const float Value);` (scope `UE::Learning::Array`)
- L383 _prototype_ `void FloatArrayCopy32(float* Dst, float* Src, const int32 Num);` (scope `UE::Learning::Array`)
- L389 _function_ `template<uint8 InDimNum, typename InElementType> inline void Zero(TLearningArrayView<InDimNum, InElementType> View)` (scope `UE::Learning::Array`) — Zero the memory of an array view
- L398 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Zero(TLearningArray<InDimNum, InElementType, Allocator>& Array)` (scope `UE::Learning::Array`) — Zero the memory of an array
- L407 _function_ `template<uint8 InDimNum, typename InElementType> inline void Zero(TLearningArrayView<InDimNum, InElementType> View, const FIndexSet Indices)` (scope `UE::Learning::Array`) — Zero the memory of an array view
- L429 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Zero(TLearningArray<InDimNum, InElementType, Allocator>& View, const FIndexSet Indices)` (scope `UE::Learning::Array`) — Zero the memory of an array view
- L451 _function_ `template<> inline void Zero<1, float>(TLearningArrayView<1, float> View)` (scope `UE::Learning::Array`) — Zero the memory of an array view
- L467 _function_ `template<> inline void Zero<2, float>(TLearningArrayView<2, float> View)` (scope `UE::Learning::Array`) — Zero the memory of an array view
- L483 _function_ `template<uint8 InDimNum, typename InElementType> inline void Set(TLearningArrayView<InDimNum, InElementType> View, const InElementType& Element)` (scope `UE::Learning::Array`) — Set each item of an array view to the given element
- L495 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Set(TLearningArray<InDimNum, InElementType, Allocator>& View, const InElementType& Element)` (scope `UE::Learning::Array`) — Set each item of an array to the given element
- L507 _function_ `template<uint8 InDimNum, typename InElementType> inline void Set(TLearningArrayView<InDimNum, InElementType> View, const InElementType& Element, const FIndexSet Indices)` (scope `UE::Learning::Array`) — Set each item of an array view to the given element
- L529 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Set(TLearningArray<InDimNum, InElementType, Allocator>& View, const InElementType& Element, const FIndexSet Indices)` (scope `UE::Learning::Array`) — Set each item of an array to the given element
- L551 _function_ `template<> inline void Set<1, float>(TLearningArrayView<1, float> View, const float& Element)` (scope `UE::Learning::Array`) — Set each item of an array view to the given element
- L570 _function_ `template<> inline void Set<2, float>(TLearningArrayView<2, float> View, const float& Element)` (scope `UE::Learning::Array`) — Set each item of an array view to the given element
- L589 _function_ `template<uint8 InDimNum, typename InElementType> inline void Copy( TLearningArrayView<InDimNum, InElementType> Dst, TLearningArrayView<InDimNum, InElementType> Src)` (scope `UE::Learning::Array`) — Copy the contents of one array view into another
- L605 _function_ `template<uint8 InDimNum, typename InElementType> inline void Copy( TLearningArrayView<InDimNum, InElementType> Dst, const TLearningArrayView<InDimNum, const InElementType> Src)` (scope `UE::Learning::Array`) — Copy the contents of one array view into another
- L621 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Copy( TLearningArray<InDimNum, InElementType, Allocator>& Dst, const TLearningArrayView<InDimNum, const InElementType> Src)` (scope `UE::Learning::Array`) — Copy the contents of one array view into another array
- L637 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Copy( TLearningArray<InDimNum, InElementType, Allocator>& Dst, const TLearningArrayView<InDimNum, InElementType> Src)` (scope `UE::Learning::Array`) — Copy the contents of one array view into another array
- L653 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Copy( TLearningArrayView<InDimNum, InElementType> Dst, const TLearningArray<InDimNum, InElementType, Allocator>& Src)` (scope `UE::Learning::Array`) — Copy the contents of one array into another array view
- L669 _function_ `template<uint8 InDimNum, typename InElementType, typename AllocatorLhs, typename AllocatorRhs> inline void Copy( TLearningArray<InDimNum, InElementType, AllocatorLhs>& Dst, const TLearningArray<InDimNum, InElementType, AllocatorRhs>& Src)` (scope `UE::Learning::Array`) — Copy the contents of one array into another array
- L685 _function_ `template<uint8 InDimNum, typename InElementType> inline void Copy( TLearningArrayView<InDimNum, InElementType> Dst, const TLearningArrayView<InDimNum, const InElementType> Src, const FIndexSet Indices)` (scope `UE::Learning::Array`) — Copy the contents of one array view into another
- L712 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Copy( TLearningArrayView<InDimNum, InElementType> Dst, const TLearningArray<InDimNum, InElementType, Allocator>& Src, const FIndexSet Indices)` (scope `UE::Learning::Array`) — Copy the contents of one array view into another
- L766 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Copy( TLearningArray<InDimNum, InElementType, Allocator>& Dst, const TLearningArrayView<InDimNum, const InElementType> Src, const FIndexSet Indices)` (scope `UE::Learning::Array`) — Copy the contents of one array view into another
- L793 _function_ `template<> inline void Copy<1, float>( TLearningArrayView<1, float> Dst, TLearningArrayView<1, float> Src)` (scope `UE::Learning::Array`) — Copy the contents of one array view into another
- L816 _function_ `template<> inline void Copy<2, float>( TLearningArrayView<2, float> Dst, TLearningArrayView<2, float> Src)` (scope `UE::Learning::Array`) — Copy the contents of one array view into another
- L839 _function_ `template<uint8 InDimNum> inline bool ShapeEqual( const TLearningArrayShape<InDimNum>& Lhs, const TLearningArrayShape<InDimNum>& Rhs)` (scope `UE::Learning::Array`) — Check if the shapes of two arrays are equal
- L855 _function_ `template<uint8 InDimNum, typename InElementType, typename AllocatorLhs, typename AllocatorRhs> inline bool Equal( const TLearningArray<InDimNum, InElementType, AllocatorLhs>& Lhs, const TLearningArray<InDimNum, InElementType, AllocatorRhs>& Rhs)` (scope `UE::Learning::Array`) — Check if the contents of one array equals the contents of another.
- L876 _function_ `template<uint8 InDimNum, typename InElementType, typename AllocatorRhs> inline bool Equal( const TLearningArrayView<InDimNum, const InElementType> Lhs, const TLearningArray<InDimNum, InElementType, AllocatorRhs>& Rhs)` (scope `UE::Learning::Array`) — Check if the contents of one array equals the contents of another.
- L897 _function_ `template<uint8 InDimNum, typename InElementType, typename AllocatorRhs> inline bool Equal( const TLearningArrayView<InDimNum, InElementType> Lhs, const TLearningArray<InDimNum, InElementType, AllocatorRhs>& Rhs)` (scope `UE::Learning::Array`) — Check if the contents of one array equals the contents of another.
- L918 _function_ `template<uint8 InDimNum, typename InElementType, typename AllocatorLhs> inline bool Equal( const TLearningArray<InDimNum, InElementType, AllocatorLhs>& Lhs, const TLearningArrayView<InDimNum, const InElementType>& Rhs)` (scope `UE::Learning::Array`) — Check if the contents of one array equals the contents of another.
- L939 _function_ `template<uint8 InDimNum, typename InElementType> inline bool Equal( const TLearningArrayView<InDimNum, const InElementType> Lhs, const TLearningArrayView<InDimNum, const InElementType> Rhs)` (scope `UE::Learning::Array`) — Check if the contents of one array equals the contents of another.
- L960 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void ShiftLeft(TLearningArray<InDimNum, InElementType, Allocator>& Array, const int64 ShiftNum)` (scope `UE::Learning::Array`) — Shift all elements in an array to the left. Data at the end of the array will remain the same.
- L972 _function_ `template<typename InElementType, typename Allocator> inline void ShiftLeft(TLearningArray<1, InElementType, Allocator>& Array, const int64 ShiftNum)` (scope `UE::Learning::Array`) — Shift all elements in an array to the left. Data at the end of the array will remain the same.
- L984 _function_ `template<uint8 InDimNum, typename InElementType> inline void ShiftLeft(TLearningArrayView<InDimNum, InElementType> Array, const int64 ShiftNum)` (scope `UE::Learning::Array`) — Shift all elements in an array to the left. Data at the end of the array will remain the same.
- L996 _function_ `template<typename InElementType> inline void ShiftLeft(TLearningArrayView<1, InElementType> Array, const int64 ShiftNum)` (scope `UE::Learning::Array`) — Shift all elements in an array to the left. Data at the end of the array will remain the same.
- L1008 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void Serialize(FArchive& Ar, TLearningArray<InDimNum, InElementType, Allocator>& Array)` (scope `UE::Learning::Array`) — Serialize an array
- L1035 _function_ `template<uint8 InDimNum, typename InElementType> inline int32 SerializationByteNum32(const TLearningArrayShape<InDimNum> Shape)` (scope `UE::Learning::Array`) — Serialization byte num
- L1044 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void SerializeToBytes32(int64& InOutOffset, TLearningArrayView<1, uint8> Bytes, const TMultiArrayShape<InDimNum> Shape, const TArray<InElementType, Allocator>& InArray)` (scope `UE::Learning::Array`) — Serialize an array to bytes
- L1061 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void SerializeToBytes32(int64& InOutOffset, TLearningArrayView<1, uint8> Bytes, const TLearningArray<InDimNum, InElementType, Allocator>& InArray)` (scope `UE::Learning::Array`) — Serialize an array to bytes
- L1078 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void DeserializeFromBytes32(int64& InOutOffset, TLearningArrayView<1, const uint8> Bytes, TArray<InElementType, Allocator>& OutArray)` (scope `UE::Learning::Array`) — Deserialize an array from bytes
- L1103 _function_ `template<uint8 InDimNum, typename InElementType, typename Allocator> inline void DeserializeFromBytes32(int64& InOutOffset, TLearningArrayView<1, const uint8> Bytes, TLearningArray<InDimNum, InElementType, Allocator>& OutArray)` (scope `UE::Learning::Array`) — Deserialize an array from bytes
- L1125 _function_ `template<typename InElementType> inline int64 IndexOf(const TLearningArrayView<1, const InElementType> Array, const InElementType& Element)` (scope `UE::Learning::Array`)
- L1138 _function_ `template<typename InElementType> inline int64 IndexOf(const TLearningArray<1, InElementType>& Array, const InElementType& Element)` (scope `UE::Learning::Array`)
- L1151 _function_ `template<typename InElementType> FString Format(const TLearningArrayView<1, const InElementType> Array, const TFunctionRef<FString(const InElementType&)> Formatter, const int32 MaxItemNum = 16)` (scope `UE::Learning::Array`)
- L1187 _function_ `static inline FString FormatFloat(const TLearningArrayView<1, const float> Array, const int32 MaxItemNum = 16)` (scope `UE::Learning::Array`)
- L1189 _function_ `return Format<float>(Array, [](const float& Value) { return FString::Printf(TEXT("%6.3f"), Value); }, MaxItem` (scope `UE::Learning::Array::FormatFloat`)
- L1192 _function_ `static inline FString FormatInt32(const TLearningArrayView<1, const int32> Array, const int32 MaxItemNum = 16)` (scope `UE::Learning::Array`)
- L1194 _function_ `return Format<int32>(Array, [](const int32& Value) { return FString::Printf(TEXT("%i"), Value); }, MaxItemNum` (scope `UE::Learning::Array::FormatInt32`)
- L1197 _function_ `static inline FString FormatUint64(const TLearningArrayView<1, const uint64> Array, const int32 MaxItemNum = 16)` (scope `UE::Learning::Array`)
- L1199 _function_ `return Format<uint64>(Array, [](const uint64& Value) { return FString::Printf(TEXT("%llu"), Value); }, MaxItemN` (scope `UE::Learning::Array::FormatUint64`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningCMAOptimizer.h` (Public)


#### struct `UE::Learning::FCMAOptimizerSettings`  
`struct FCMAOptimizerSettings`  
_L14-23_
- desc: Settings for the CMA Optimizer
- L18 _public member_ `float InitialStepSize = 0.3f;` — The size of the initial exploration region for CMA. Larger introduces more exploration but may have worse initial results or cause longer convergence
- L22 _public member_ `float SurvialRatio = 0.5f;` — What ratio of samples are used to update the covariance matrix and how many are discarded. Larger values can speed up convergence on flat gradients but will make things worse on complex loss landscapes

#### struct `UE::Learning::FCMAOptimizer`  
`struct FCMAOptimizer : public IOptimizer`  
_L30-72_
- inherits: `IOptimizer`
- desc: CMA Optimizer Black box optimizer based on Covariance Matrix Adaption
- L32 _public prototype_ `FCMAOptimizer(const uint32 Seed, const FCMAOptimizerSettings& InSettings = FCMAOptimizerSettings());`
- L34 _public prototype_ `virtual void Resize(const int32 SampleNum, const int32 DimensionsNum) override final;`
- L36 _public prototype_ `virtual void Reset( TLearningArrayView<2, float> OutSamples, const TLearningArrayView<1, const float> InitialGuess) override final;`
- L40 _public prototype_ `virtual void Update( TLearningArrayView<2, float> InOutSamples, const TLearningArrayView<1, const float> Losses, const ELogSetting LogSettings = ELogSetting::Normal) override final;`
- L45 _public prototype_ `static int32 DefaultSampleNum(const int32 DimensionNum);`
- L49 _private prototype_ `void Sample(TLearningArrayView<2, float> OutSamples);`
- L51 _private member_ `uint32 Seed = 0;`
- L52 _private member_ `FCMAOptimizerSettings Settings;`
- L54 _private member_ `int32 Iterations = 0;`
- L55 _private member_ `float Sigma = 0.3f;`
- L56 _private member_ `TLearningArray<1, float> PathSigma;`
- L57 _private member_ `TLearningArray<1, float> PathCovariance;`
- L58 _private member_ `TLearningArray<1, float> Mean;`
- L59 _private member_ `TLearningArray<2, float> Covariance;`
- L61 _private member_ `int32 Mu = 0;`
- L62 _private member_ `float MuEff = 0.0f;`
- L63 _private member_ `TLearningArray<1, float> Weights;`
- L65 _private member_ `TLearningArray<1, float> OldMean;`
- L66 _private member_ `TLearningArray<1, int32> LossRanking;`
- L67 _private member_ `TLearningArray<1, float> UpdateDirection;`
- L68 _private member_ `TLearningArray<2, float> CovarianceTransform;`
- L69 _private member_ `TLearningArray<2, float> CovarianceInverseSqrt;`
- L71 _private member_ `TLearningArray<2, float> GaussianSamples;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEARNING_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningCompletion.h` (Public)


#### enum `UE::Learning::ECompletionMode`  
`enum class ECompletionMode : uint8`  
_L14-24_
- desc: Completion Mode
- L17 _public enumerator_ `Running = 0` — Episode is still running
- L20 _public enumerator_ `Truncated = 1` — Episode ended early but was still in progress. Value function will be used to estimate final return.
- L23 _public enumerator_ `Terminated = 2` — Episode ended early and zero reward was expected for all future steps.

#### struct `UE::Learning::FResetInstanceBuffer`  
`struct FResetInstanceBuffer`  
_L30-44_
- desc: This object stores essentially a list of instances that need to be reset. It can be filled based on the completion status or manually.
- L32 _public prototype_ `void Reserve(const int32 InMaxInstanceNum);`
- L34 _public prototype_ `void SetResetInstances(const FIndexSet Instances);`
- L35 _public prototype_ `void SetResetInstancesFromCompletions(const TLearningArrayView<1, const ECompletionMode> Completions, const FIndexSet Instances);`
- L36 _public prototype_ `const int32 GetResetInstanceNum() const;`
- L37 _public prototype_ `const FIndexSet GetResetInstances() const;`
- L38 _public prototype_ `const TArray<int32>& GetResetInstancesArray() const;`
- L42 _private member_ `FIndexSet ResetInstancesSet;`
- L43 _private member_ `TArray<int32> ResetInstances;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEARNING_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Learning` (scope `UE`)
- L46 _namespace_ `namespace Completion` (scope `UE::Learning`)
- L51 _prototype_ `const TCHAR* CompletionModeString(const ECompletionMode Completion);` (scope `UE::Learning::Completion`) — Converts a ECompletionMode into a string.
- L58 _prototype_ `ECompletionMode Or(const ECompletionMode Lhs, const ECompletionMode Rhs);` (scope `UE::Learning::Completion`) — Takes the logical Or of completions. More specifically, if either completion is `Terminated` that will be the result of this operator, otherwise either completion being `Truncated` takes priority over either being `Running`. Put simply: Terminated > Truncated > Running
- L69 _prototype_ `void EvaluateEndOfEpisodeCompletions( TLearningArrayView<1, ECompletionMode> OutCompletions, const TLearningArrayView<1, const int32> EpisodeStepNums, const int32 EpisodeMaxStepNum, const FIndexSet Instances);` (scope `UE::Learning::Completion`) — Set completions for all instances whose episode has reached the max number of steps. @param OutCompletions					Output buffer to write completions to @param EpisodeStepNums				Number of steps taken by each instance @param EpisodeMaxStepNum				Maximum number of allowed steps @param Instances						Instances to process

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningCritic.h` (Public)


#### struct `UE::Learning::FNeuralNetworkCritic`  
`struct FNeuralNetworkCritic`  
_L17-62_
- desc: Neural-network based critic object. Stores various settings and intermediate storage required to evaluate the given network for the provided number of instances.
- L28 _public prototype_ `FNeuralNetworkCritic( const int32 InMaxInstanceNum, const int32 InObservationEncodedNum, const int32 InMemoryStateNum, const TSharedPtr<FNeuralNetwork>& InNeuralNetwork, const FNeuralNetworkInferenceSettings& InInferenceSettings = FNeuralNetworkInferenceSettings());` — Create a new Critic Object which takes the encoded observation state, and the memory state, and outputs the expected discounted returns. @param InMaxInstanceNum				Maximum number of instances @param InObservationEncodedNum		Size of the encoded observation vector @param InMemoryStateNum				Size of the memory state @param InNeuralNetwork				Neural network object @param InInferenceSettings			Inference settings
- L43 _public prototype_ `void Evaluate( TLearningArrayView<1, float> OutputReturns, const TLearningArrayView<2, const float> InputObservationVectorsEncoded, const TLearningArrayView<2, const float> InputMemoryState, const FIndexSet Instances);` — Evaluate the Critic @param OutputReturns						Output expected discounted returns of shape (MaxInstanceNum) @param InputObservationVectorsEncoded	Input encoded observation vectors of shape (MaxInstanceNum, ObservationEncodedNum) @param InputMemoryState					Input memory state of shape (MaxInstanceNum, MemoryStateNum) @param Instances							Set of instances to evaluate
- L50 _public prototype_ `void UpdateNeuralNetwork(const TSharedPtr<FNeuralNetwork>& NewNeuralNetwork);` — Sets the NeuralNetwork and re-creates the NeuralNetworkInference object
- L53 _public prototype_ `const TSharedPtr<FNeuralNetwork>& GetNeuralNetwork() const;` — Gets the NeuralNetwork associated with this Critic
- L57 _private member_ `int32 ObservationEncodedNum = 0;`
- L58 _private member_ `int32 MemoryStateNum = 0;`
- L59 _private member_ `TSharedPtr<FNeuralNetworkFunction> NeuralNetworkFunction;`
- L61 _private member_ `TLearningArray<2, float> Input;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNING_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningFrameAttribute.h` (Public)


#### struct `UE::Learning::FFrameAttribute`  
`struct FFrameAttribute`  
_L27-89_
- desc: A FFrameAttribute represents a attribute associated with every frame in a FFrameRangeSet. An attribute is made up of multiple "channels" such as the X, Y, Z components of a location. The data for the attribute is stored in one large flat array of shape (ChannelNum, TotalFrameNum). This means the data is stored in a way designed for SoA access by default. Some helper functions are provided for accessing slices of this data according to various range properties. Also provided are many "operators" which allow for batched operations on attributes to create new attributes such as adding or subtracting attribute values. This operations are very efficient as they are computed across all frames in the attribute in batch and can be optimized using ISPC. If you perform a binary operation on two channels with different frames in the range sets then it will construct a new channel which is the intersection of those two inputs.
- L32 _public prototype_ `void Check() const;` — Check if the FrameAttribute is well-formed.
- L35 _public prototype_ `bool IsEmpty() const;` — True if the FrameAttribute is Empty, otherwise false
- L38 _public prototype_ `void Empty();` — Empties the FrameAttribute
- L41 _public prototype_ `const FFrameRangeSet& GetFrameRangeSet() const;` — Gets the internal FrameRangeSet associated to this attribute
- L44 _public prototype_ `int32 GetTotalFrameNum() const;` — Gets the total number of frames for this attribute
- L47 _public prototype_ `int32 GetTotalRangeNum() const;` — Gets the total number of ranges for this attribute
- L50 _public prototype_ `int32 GetChannelNum() const;` — Gets the number of channels in this attribute
- L53 _public prototype_ `TLearningArrayView<2, const float> GetAttributeData() const;` — Gets a view of the complete large array of attribute data stored as (ChannelNum, TotalFrameNum)
- L56 _public prototype_ `TLearningArrayView<1, const float> GetChannelAttributeData(const int32 ChannelIdx) const;` — Gets a view of the complete attribute data for a single channel
- L59 _public prototype_ `const float& GetChannelAttributeDataAtFrame(const int32 ChannelIdx, const int32 FrameIdx) const;` — Gets the attribute value for a given channel and frame index
- L62 _public prototype_ `TLearningArrayView<1, const float> GetChannelEntryRangeAttributeData(const int32 ChannelIdx, const int32 EntryIdx, const int32 RangeIdx) const;` — Gets the attribute data associated with a single channel, and range
- L65 _public prototype_ `TLearningArrayView<1, const float> GetChannelRangeAttributeData(const int32 ChannelIdx, const int32 RangeOffset, const int32 RangeLength) const;` — Gets the attribute data associated with range offset and length
- L68 _public prototype_ `TLearningArrayView<2, float> GetAttributeData();` — Gets a view of the complete large array of attribute data stored as (ChannelNum, TotalFrameNum)
- L71 _public prototype_ `TLearningArrayView<1, float> GetChannelAttributeData(const int32 ChannelIdx);` — Gets a view of the complete attribute data for a single channel
- L74 _public prototype_ `float& GetChannelAttributeDataAtFrame(const int32 ChannelIdx, const int32 FrameIdx);` — Gets the attribute value for a given channel and frame index
- L77 _public prototype_ `TLearningArrayView<1, float> GetChannelEntryRangeAttributeData(const int32 ChannelIdx, const int32 EntryIdx, const int32 RangeIdx);` — Gets the attribute data associated with a single channel, and range
- L80 _public prototype_ `TLearningArrayView<1, float> GetChannelRangeAttributeData(const int32 ChannelIdx, const int32 RangeOffset, const int32 RangeLength);` — Gets the attribute data associated with range offset and length
- L85 _public member_ `FFrameRangeSet FrameRangeSet;` — The internal associate FrameRangeSet
- L88 _public member_ `TLearningArray<2, float> AttributeData;` — The large flat array of attribute data of shape (ChannelNum, TotalFrameNum)

#### enum `UE::Learning::FrameAttribute::EPhaseExtrapolationMode`  
`enum class EPhaseExtrapolationMode : uint8`  
_L660-667_
- desc: Mode for handling edges in phase extraction
- L663 _public enumerator_ `Repeat = 0` — Repeats the phase value at the start and end frames
- L666 _public enumerator_ `Extrapolate = 1` — Extrapolates the phase value using the nearest pair of frames

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LEARNING_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Learning` (scope `UE`)
- L91 _namespace_ `namespace FrameAttribute` (scope `UE::Learning`)
- L94 _typedef_ `using ReduceOpFunction = TFunctionRef<void( const FFrameAttribute& In, const TLearningArrayView<1, const int32> RangeOffsets, const TLearningArrayView<1, const int32> RangeLengths)>;` (scope `UE::Learning::FrameAttribute`) — Reduce op function. Takes as input a single frame attribute and a set of ranges and lengths for that attribute.
- L100 _typedef_ `using NullaryOpFunction = TFunctionRef<void( FFrameAttribute& Out, const TLearningArrayView<1, const int32> RangeOffsets, const TLearningArrayView<1, const int32> RangeLengths)>;` (scope `UE::Learning::FrameAttribute`) — Nullary op function. Produces as output a single frame attribute given a set of ranges and lengths for that attribute.
- L106 _typedef_ `using UnaryOpFunction = TFunctionRef<void( FFrameAttribute& Out, const FFrameAttribute& In, const TLearningArrayView<1, const int32> RangeOffsets, const TLearningArrayView<1, const int32> RangeLengths)>;` (scope `UE::Learning::FrameAttribute`) — Unary op function. Takes a single frame attribute as input and produces as output a single frame attribute.
- L113 _typedef_ `using InplaceOpFunction = TFunctionRef<void( FFrameAttribute& InOut, const TLearningArrayView<1, const int32> RangeOffsets, const TLearningArrayView<1, const int32> RangeLengths)>;` (scope `UE::Learning::FrameAttribute`) — In-place op function. Takes a single frame attribute and modifies it in-place.
- L119 _typedef_ `using BinaryOpFunction = TFunctionRef<void( FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs, const TLearningArrayView<1, const int32> OutRangeOffsets, const TLearningArrayView<1, const int32> LhsRangeOffsets, const TLearningArrayView<1, const int32> RhsRangeOffsets, const TLearningArrayView<1, const int32> RangeLengths)>;` (scope `UE::Learning::FrameAttribute`) — Binary op function. Takes a two frame attributes as input and produces as output a single frame attribute.
- L129 _typedef_ `using ConstFrameAttributePtr = const FFrameAttribute*;` (scope `UE::Learning::FrameAttribute`) — Convenience type to make the definition and usage of NaryOp easier
- L132 _typedef_ `using NaryOpFunction = TFunctionRef<void( FFrameAttribute& Out, const TArrayView<const ConstFrameAttributePtr> In, const TLearningArrayView<1, const int32> OutRangeOffsets, const TArrayView<const TLearningArrayView<1, const int32>> InRangeOffsets, const TLearningArrayView<1, const int32> RangeLengths)>;` (scope `UE::Learning::FrameAttribute`) — Nary op function. Takes a multiple frame attributes as input and produces as output a single frame attribute.
- L140 _prototype_ `bool Equal(const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Checks if two frame attributes are equal
- L143 _prototype_ `void Intersection(FFrameAttribute& OutFrameAttribute, const FFrameAttribute& FrameAttribute, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameAttribute`) — Computes the intersection of a frame attribute and frame range set
- L146 _prototype_ `void NonZeroFrameRangeSet(FFrameRangeSet& OutFrameRangeSet, const FFrameAttribute& FrameAttribute, const int32 ChannelIdx);` (scope `UE::Learning::FrameAttribute`) — Computes the frame range set where the given channel is non-zero in the frame attribute.
- L149 _prototype_ `void Concat(FFrameAttribute& Out, const TArrayView<const ConstFrameAttributePtr> In);` (scope `UE::Learning::FrameAttribute`) — Concatenates the given frame attributes together.
- L152 _prototype_ `void ReduceOp( const FFrameAttribute& In, const ReduceOpFunction Op);` (scope `UE::Learning::FrameAttribute`) — Computes a reduction on a frame attribute
- L157 _prototype_ `void NullaryOp( FFrameAttribute& Out, const int32 OutChannelNum, const FFrameRangeSet& FrameRangeSet, const NullaryOpFunction Op);` (scope `UE::Learning::FrameAttribute`) — Creates a frame attribute from zero arguments and the given op
- L164 _prototype_ `void UnaryOp( FFrameAttribute& Out, const int32 OutChannelNum, const FFrameAttribute& In, const UnaryOpFunction Op);` (scope `UE::Learning::FrameAttribute`) — Creates a frame attribute from another and the given op
- L171 _prototype_ `void InplaceOp( FFrameAttribute& InOut, const InplaceOpFunction Op);` (scope `UE::Learning::FrameAttribute`) — Modifies a frame attribute in-place using the given op
- L176 _prototype_ `void BinaryOp( FFrameAttribute& Out, const int32 OutChannelNum, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs, const BinaryOpFunction Op);` (scope `UE::Learning::FrameAttribute`) — Creates a frame attribute from two others and the given op. Performs an intersection of the Lhs and Rhs if they do not match.
- L184 _prototype_ `void NaryOp( FFrameAttribute& Out, const int32 OutChannelNum, const TArrayView<const ConstFrameAttributePtr> Inputs, const NaryOpFunction Op);` (scope `UE::Learning::FrameAttribute`) — Creates a frame attribute from multiple others and the given op.
- L192 _prototype_ `bool FindMinimum( int32& OutChannelIdx, int32& OutFrameIdx, float& OutMinimumValue, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Find the channel and frame with the smallest value
- L199 _prototype_ `bool FindMaximum( int32& OutChannelIdx, int32& OutFrameIdx, float& OutMaximumValue, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Find the channel and frame with the largest value
- L207 _prototype_ `void Select(FFrameAttribute& Out, const FFrameAttribute& Cond, const FFrameAttribute& True, const FFrameAttribute& False);` (scope `UE::Learning::FrameAttribute`) — Select between True and False frame attributes based on Cond.
- L211 _prototype_ `void Zeros(FFrameAttribute& Out, const FFrameRangeSet& FrameRangeSet, const int32 ChannelNum);` (scope `UE::Learning::FrameAttribute`) — Create a frame attribute made up of zeros
- L214 _prototype_ `void Ones(FFrameAttribute& Out, const FFrameRangeSet& FrameRangeSet, const int32 ChannelNum);` (scope `UE::Learning::FrameAttribute`) — Create a frame attribute made up of ones
- L217 _prototype_ `void Fill(FFrameAttribute& Out, const FFrameRangeSet& FrameRangeSet, const TLearningArrayView<1, const float> Values);` (scope `UE::Learning::FrameAttribute`) — Create a frame attribute filled with the given value at each frame
- L221 _prototype_ `void Add(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Add two frame attributes. Channel numbers must match.
- L224 _prototype_ `void Sub(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Subtract two frame attributes. Channel numbers must match.
- L227 _prototype_ `void Mul(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Multiply two frame attributes. Channel numbers must match.
- L230 _prototype_ `void Div(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Divide two frame attributes. Channel numbers must match.
- L233 _prototype_ `void Max(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the component-wise maximum of two frame attributes. Channel numbers must match.
- L236 _prototype_ `void Min(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the component-wise minimum of two frame attributes. Channel numbers must match.
- L240 _prototype_ `void Dot(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Compute the dot product of two frame attributes. Channel numbers must match.
- L243 _prototype_ `void Cross(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Compute the cross product of two frame attributes. Both arguments are assumed to have 3 channels.
- L246 _prototype_ `void Copy(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Copy a frame attribute.
- L249 _prototype_ `void Repeat(FFrameAttribute& Out, const int32 ChannelNum, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Create a frame attribute filled with the given single channel frame attribute at each frame
- L252 _prototype_ `void Neg(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Negate a frame attribute.
- L255 _prototype_ `void Inv(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Invert a frame attribute (compute 1/x).
- L258 _prototype_ `void Abs(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the absolute value of a frame attribute.
- L261 _prototype_ `void Log(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the log of a frame attribute.
- L264 _prototype_ `void Exp(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the exp of a frame attribute.
- L267 _prototype_ `void Sqrt(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the sqrt of a frame attribute.
- L270 _prototype_ `void Sin(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the sin of a frame attribute.
- L273 _prototype_ `void Cos(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the cos of a frame attribute.
- L276 _prototype_ `void Atan2(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Compute the atan2 of two frame attributes.
- L279 _prototype_ `void NegInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Compute the negation of a frame attribute in place.
- L282 _prototype_ `void InvInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Compute 1/x of a frame attribute in place.
- L285 _prototype_ `void AbsInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Compute the absolute value of a frame attribute in place.
- L288 _prototype_ `void LogInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Compute the log of a frame attribute in place.
- L291 _prototype_ `void ExpInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Compute the exp of a frame attribute in place.
- L294 _prototype_ `void SqrtInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Compute the square root of a frame attribute in place.
- L297 _prototype_ `void ApproxAcosInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Compute the approximate acos of a frame attribute in place.
- L300 _prototype_ `void NormalizeInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Normalize the frame attribute in place.
- L303 _prototype_ `void RepeatFirstRangeEntryInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Repeats the first entry in the range across the rest of the range
- L307 _prototype_ `void Length(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the length of a frame attribute over the channels dimension.
- L310 _prototype_ `void Normalize(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Normalize a frame attribute over the channels dimension.
- L313 _prototype_ `void Index(FFrameAttribute& Out, const FFrameAttribute& In, const int32 ChannelIdx);` (scope `UE::Learning::FrameAttribute`) — Extract a single channel from frame attribute.
- L316 _prototype_ `void Slice(FFrameAttribute& Out, const FFrameAttribute& In, const int32 StartChannelIdx, const int32 ChannelNum);` (scope `UE::Learning::FrameAttribute`) — Extract a range of channels from frame attribute.
- L319 _prototype_ `void AddConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Add a constant value to a frame attribute. Channel number must match the size of Rhs.
- L322 _prototype_ `void SubConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Subtract a constant value to a frame attribute. Channel number must match the size of Rhs.
- L325 _prototype_ `void MulConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Multiply a frame attribute by a constant value. Channel number must match the size of Rhs.
- L328 _prototype_ `void DivConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Divide a frame attribute by a constant value. Channel number must match the size of Rhs.
- L331 _prototype_ `void MaxConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Compute the component-wise maximum of a constant value and a frame attribute. Channel number must match the size of Rhs.
- L334 _prototype_ `void MinConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Compute the component-wise minimum of a constant value and a frame attribute. Channel number must match the size of Rhs.
- L338 _prototype_ `void ConstantAdd(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Add a constant value to a frame attribute. Channel number must match the size of Lhs.
- L341 _prototype_ `void ConstantSub(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Subtract a constant value to a frame attribute. Channel number must match the size of Lhs.
- L344 _prototype_ `void ConstantMul(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Multiply a frame attribute by a constant value. Channel number must match the size of Lhs.
- L347 _prototype_ `void ConstantDiv(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Divide a frame attribute by a constant value. Channel number must match the size of Lhs.
- L350 _prototype_ `void ConstantMax(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Compute the component-wise maximum of a constant value and a frame attribute. Channel number must match the size of Lhs.
- L353 _prototype_ `void ConstantMin(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Compute the component-wise minimum of a constant value and a frame attribute. Channel number must match the size of Lhs.
- L358 _prototype_ `void ConstantDot(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Gets the dot product with a constant value. Channel number must match the size of Lhs.
- L361 _prototype_ `void ConstantSquaredDist(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Gets the squared euclidean distance to a constant value. Channel number must match the size of Lhs.
- L364 _prototype_ `void ConstantDist(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Gets the euclidean distance to a constant value. Channel number must match the size of Lhs.
- L368 _prototype_ `void AddConstantInplace(FFrameAttribute& InOut, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Add a frame attribute by a constant value in-place. Channel number must match the size of Rhs.
- L371 _prototype_ `void SubConstantInplace(FFrameAttribute& InOut, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Subtract a frame attribute by a constant value in-place. Channel number must match the size of Rhs.
- L374 _prototype_ `void MulConstantInplace(FFrameAttribute& InOut, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Multiply a frame attribute by a constant value in-place. Channel number must match the size of Rhs.
- L377 _prototype_ `void DivConstantInplace(FFrameAttribute& InOut, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Divide a frame attribute by a constant value in-place. Channel number must match the size of Rhs.
- L381 _prototype_ `void Sum(FFrameAttribute& Out, const TArrayView<const ConstFrameAttributePtr> Inputs);` (scope `UE::Learning::FrameAttribute`) — Compute the sum of an array of frame attributes. Channel numbers must match.
- L384 _prototype_ `void Prod(FFrameAttribute& Out, const TArrayView<const ConstFrameAttributePtr> Inputs);` (scope `UE::Learning::FrameAttribute`) — Compute the product of an array of frame attributes. Channel numbers must match.
- L388 _prototype_ `void LogicalAnd(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the logical and of two frame attributes. Channel numbers must match.
- L391 _prototype_ `void LogicalOr(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the logical or of two frame attributes. Channel numbers must match.
- L394 _prototype_ `void LogicalNot(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the logical not of a frame attribute.
- L398 _prototype_ `void Gt(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in one frame attribute are greater than another. Channel numbers must match.
- L401 _prototype_ `void Ge(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in one frame attribute are greater than or equal to another. Channel numbers must match.
- L404 _prototype_ `void Lt(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in one frame attribute are less than another. Channel numbers must match.
- L407 _prototype_ `void Le(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in one frame attribute are less than or equal to another. Channel numbers must match.
- L410 _prototype_ `void Eq(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in one frame attribute are equal to another. Channel numbers must match.
- L413 _prototype_ `void Neq(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in one frame attribute are not equal to another. Channel numbers must match.
- L417 _prototype_ `void GtConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are greater than a constant. Channel number must match the size of Rhs.
- L420 _prototype_ `void GeConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are greater than or equal to a constant. Channel number must match the size of Rhs.
- L423 _prototype_ `void LtConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are less than a constant. Channel number must match the size of Rhs.
- L426 _prototype_ `void LeConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are greater than or equal to a constant. Channel number must match the size of Rhs.
- L429 _prototype_ `void EqConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are equal to a constant. Channel number must match the size of Rhs.
- L432 _prototype_ `void NeqConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const TLearningArrayView<1, const float> Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are not equal to a constant. Channel number must match the size of Rhs.
- L436 _prototype_ `void ConstantGt(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are greater than a constant. Channel number must match the size of Lhs.
- L439 _prototype_ `void ConstantGe(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are greater than or equal to a constant. Channel number must match the size of Lhs.
- L442 _prototype_ `void ConstantLt(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are less than a constant. Channel number must match the size of Lhs.
- L445 _prototype_ `void ConstantLe(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are greater than or equal to a constant. Channel number must match the size of Lhs.
- L448 _prototype_ `void ConstantEq(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are equal to a constant. Channel number must match the size of Lhs.
- L451 _prototype_ `void ConstantNeq(FFrameAttribute& Out, const TLearningArrayView<1, const float> Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes if the values in a frame attribute are not equal to a constant. Channel number must match the size of Lhs.
- L455 _prototype_ `void FilterGaussian(FFrameAttribute& Out, const FFrameAttribute& In, const float StdInFrames);` (scope `UE::Learning::FrameAttribute`) — Applies a Gaussian smoothing filter to the ranges of values in the frame attribute.
- L458 _prototype_ `void FilterMajorityVote(FFrameAttribute& Out, const FFrameAttribute& In, const int32 FilterWidthFrames);` (scope `UE::Learning::FrameAttribute`) — Applies a Majority Vote filter to the ranges of values in the frame attribute.
- L461 _prototype_ `void FilterSavGol(FFrameAttribute& Out, const FFrameAttribute& In, const int32 FilterWidthFrames, const int32 PolynomialDegree, const bool bGaussianWindowed);` (scope `UE::Learning::FrameAttribute`) — Applies a SavGol filter to the ranges of values in the frame attribute.
- L465 _prototype_ `void Mean(TLearningArrayView<1, float> OutMean, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the mean across all frames. OutMean should be size of the number of channels
- L468 _prototype_ `void MeanStd(TLearningArrayView<1, float> OutMean, TLearningArrayView<1, float> OutStd, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the mean and std across all frames. OutMean and OutStd should be size of the number of channels
- L471 _prototype_ `void LogMeanStd(TLearningArrayView<1, float> OutMean, TLearningArrayView<1, float> OutLogStd, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the mean and log std across all frames in the log space. OutMean and OutLogStd should be size of the number of channels
- L474 _prototype_ `void MinMax(TLearningArrayView<1, float> OutMin, TLearningArrayView<1, float> OutMax, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the min and max across all frames. OutMin and OutMax should be size of the number of channels
- L477 _prototype_ `void AngularMean(TLearningArrayView<1, float> OutMean, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the angular mean across all frames.
- L480 _prototype_ `void AngularMeanStd(TLearningArrayView<1, float> OutMean, TLearningArrayView<1, float> OutStd, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the angular mean and std across all frames.
- L484 _prototype_ `void QuatMul(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion multiplication of two frame attributes. Both arguments are assumed to have 4 channels.
- L487 _prototype_ `void QuatDiv(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion division of two frame attributes. Both arguments are assumed to have 4 channels.
- L490 _prototype_ `void QuatInv(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the quaternion inverse of a frame attribute. Argument is assumed to have 4 channels.
- L493 _prototype_ `void QuatAbs(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the quaternion closest to the identity quaternion for a frame attribute. Argument is assumed to have 4 channels.
- L496 _prototype_ `void QuatToRotationVector(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute a rotation vector from a quaternion. Argument is assumed to have 4 channels.
- L499 _prototype_ `void QuatFromRotationVector(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute a quaternion from a rotation vector. Argument is assumed to have 3 channels.
- L502 _prototype_ `void QuatFromBasisDirections(FFrameAttribute& Out, const FFrameAttribute& Forward, const FFrameAttribute& Right, const FFrameAttribute& Up);` (scope `UE::Learning::FrameAttribute`) — Compute a quaternion from a set of basis directions. Arguments are assumed to have 3 channels.
- L505 _prototype_ `void QuatFromPitchYawRoll(FFrameAttribute& Out, const FFrameAttribute& Pitch, const FFrameAttribute& Yaw, const FFrameAttribute& Roll);` (scope `UE::Learning::FrameAttribute`) — Compute a quaternion from pitch, yaw and roll.
- L508 _prototype_ `void QuatInvMul(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion inverse multiplication of two frame attributes. Both arguments are assumed to have 4 channels.
- L511 _prototype_ `void QuatMulInv(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion multiplication inverse of two frame attributes. Both arguments are assumed to have 4 channels.
- L514 _prototype_ `void QuatRotate(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the rotation of the Rhs by the Lhs quaternion. Lhs is assumed to have 4 channels, and Rhs is assumed to have 3.
- L517 _prototype_ `void QuatUnrotate(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the inverse rotation of the Rhs by the Lhs quaternion. Lhs is assumed to have 4 channels, and Rhs is assumed to have 3.
- L520 _prototype_ `void QuatBetween(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the shortest rotation between two vectors. Both arguments are assumed to have 3 channels.
- L523 _prototype_ `void QuatMulConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FQuat4f Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion multiplication of a frame attribute by the given quaternion. Lhs is assumed to have 4 channels.
- L526 _prototype_ `void QuatDivConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FQuat4f Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion division of a frame attribute by the given quaternion. Lhs is assumed to have 4 channels.
- L529 _prototype_ `void QuatInvMulConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FQuat4f Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion inverse multiplication of a frame attribute by the given quaternion. Lhs is assumed to have 4 channels.
- L532 _prototype_ `void QuatMulInvConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FQuat4f Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion multiplication inverse of a frame attribute by the given quaternion. Lhs is assumed to have 4 channels.
- L535 _prototype_ `void QuatRotateConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FVector3f Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion rotation of the given vector by a frame attribute. Lhs is assumed to have 4 channels.
- L538 _prototype_ `void QuatUnrotateConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FVector3f Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion inverse rotation of the given vector by a frame attribute. Lhs is assumed to have 4 channels.
- L541 _prototype_ `void QuatBetweenConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FVector3f Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion between the given frame attribute and vector. Lhs is assumed to have 3 channels.
- L544 _prototype_ `void QuatApproxShortestAngleBetweenConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FQuat4f Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes a fast approximation of the shortest angle between the given frame attribute and the quaternion. Lhs is assumed to have 4 channels.
- L547 _prototype_ `void QuatConstantMul(FFrameAttribute& Out, const FQuat4f Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion multiplication of a frame attribute by the given quaternion. Rhs is assumed to have 4 channels.
- L550 _prototype_ `void QuatConstantDiv(FFrameAttribute& Out, const FQuat4f Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion division of a frame attribute by the given quaternion. Rhs is assumed to have 4 channels.
- L553 _prototype_ `void QuatConstantInvMul(FFrameAttribute& Out, const FQuat4f Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion inverse multiplication of a frame attribute by the given quaternion. Rhs is assumed to have 4 channels.
- L556 _prototype_ `void QuatConstantMulInv(FFrameAttribute& Out, const FQuat4f Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion multiplication inverse of a frame attribute by the given quaternion. Rhs is assumed to have 4 channels.
- L559 _prototype_ `void QuatConstantRotate(FFrameAttribute& Out, const FQuat4f Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion rotation of the given frame attribute. Rhs is assumed to have 3 channels.
- L562 _prototype_ `void QuatConstantUnrotate(FFrameAttribute& Out, const FQuat4f Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion inverse rotation of the given frame attribute. Rhs is assumed to have 3 channels.
- L565 _prototype_ `void QuatConstantBetween(FFrameAttribute& Out, const FVector3f Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion between the given frame attribute and vector. Rhs is assumed to have 3 channels.
- L568 _prototype_ `void QuatMeanStd(FQuat4f& OutMean, FVector3f& OutStd, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the quaternion mean and std across all frames.
- L571 _prototype_ `void QuatPitch(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the pitch component of a quaternion rotation. Argument is assumed to have 4 channels.
- L574 _prototype_ `void QuatYaw(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the yaw component of a quaternion rotation. Argument is assumed to have 4 channels.
- L577 _prototype_ `void QuatRoll(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes the roll component of a quaternion rotation. Argument is assumed to have 4 channels.
- L581 _prototype_ `void WrapAngleInplace(FFrameAttribute& InOut);` (scope `UE::Learning::FrameAttribute`) — Wraps a frame attribute in-place into the range -UE_PI, UE_PI
- L584 _prototype_ `void AngleToDirection3D(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes a 3D direction from a scalar angle, leaving the Z component as zero
- L587 _prototype_ `void Direction3DToAngle(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Computes an angle from a 3D direction ignoring the Z component
- L591 _prototype_ `void TransformMake(FFrameAttribute& Out, const FFrameAttribute& Location, const FFrameAttribute& Rotation, const FFrameAttribute& Scale);` (scope `UE::Learning::FrameAttribute`) — Make a transform attribute from a location, rotation, and scale
- L594 _prototype_ `void TransformMake(FFrameAttribute& Out, const FFrameAttribute& Location, const FFrameAttribute& Rotation);` (scope `UE::Learning::FrameAttribute`) — Make a transform attribute from a location and rotation
- L597 _prototype_ `void TransformMul(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the transform multiplication of two frame attributes. Both arguments are assumed to have 10 channels.
- L600 _prototype_ `void TransformDiv(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the transform division of two frame attributes. Both arguments are assumed to have 10 channels.
- L603 _prototype_ `void TransformMulConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FTransform3f& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the transform multiplication of a frame attribute and a constant value. Argument is assumed to have 10 channels.
- L606 _prototype_ `void TransformDivConstant(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FTransform3f& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the transform division of a frame attribute and a constant value. Argument is assumed to have 10 channels.
- L609 _prototype_ `void TransformConstantMul(FFrameAttribute& Out, const FTransform3f& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the transform multiplication of a frame attribute and a constant value. Argument is assumed to have 10 channels.
- L612 _prototype_ `void TransformConstantDiv(FFrameAttribute& Out, const FTransform3f& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Computes the transform division of a frame attribute and a constant value. Argument is assumed to have 10 channels.
- L615 _prototype_ `void TransformInv(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Compute the transform inverse of a frame attribute. Argument is assumed to have 10 channels.
- L618 _prototype_ `void TransformLocation(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Gets the location part of a transform. Argument is assumed to have 10 channels.
- L621 _prototype_ `void TransformRotation(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Gets the rotation part of a transform. Argument is assumed to have 10 channels.
- L624 _prototype_ `void TransformScale(FFrameAttribute& Out, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Gets the scale part of a transform. Argument is assumed to have 10 channels.
- L627 _prototype_ `void TransformApplyConstantLocation(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FVector3f& Rhs);` (scope `UE::Learning::FrameAttribute`) — Applies the transform to a location
- L630 _prototype_ `void TransformApplyConstantDirection(FFrameAttribute& Out, const FFrameAttribute& Lhs, const FVector3f& Rhs);` (scope `UE::Learning::FrameAttribute`) — Applies the transform to a direction
- L633 _prototype_ `void TransformConstantApply(FFrameAttribute& Out, const FTransform3f& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Applies the transform to a vector
- L636 _prototype_ `void TransformConstantApplyNoTranslation(FFrameAttribute& Out, const FTransform3f& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Applies the transform to a vector without translation (i.e. rotation and scale only)
- L639 _prototype_ `void TransformConstantApplyNoTranslationScale(FFrameAttribute& Out, const FTransform3f& Lhs, const FFrameAttribute& Rhs);` (scope `UE::Learning::FrameAttribute`) — Applies the transform to a vector without translation or scale (i.e. rotation only)
- L643 _prototype_ `void InertializationDistanceConstant( FFrameAttribute& Out, const FFrameAttribute& LhsPos, const FFrameAttribute& LhsVel, const TArrayView<const float> RhsLoc, const TArrayView<const float> RhsVel, const float BlendTime, const float LocWeight, const float VelWeight);` (scope `UE::Learning::FrameAttribute`) — Inertialization distance for a cubic inertialization function. See: https://theorangeduck.com/page/inertialization-transition-cost
- L654 _prototype_ `void LocationDistanceTraveled(TArrayView<float> OutDistancesTraveled, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Gets distance traveled of each range in a location frame attribute
- L657 _prototype_ `void QuatAngleTraveled(TArrayView<float> OutAnglesTraveled, const FFrameAttribute& In);` (scope `UE::Learning::FrameAttribute`) — Gets angle traveled of each range in a quat frame attribute
- L670 _prototype_ `void ExtractPhase( FFrameAttribute& Out, const FFrameRangeSet& FrameRangeSet, const FFrameSet& ZeroPhaseFrames, const FFrameSet& HalfPhaseFrames, const EPhaseExtrapolationMode Extrapolation = EPhaseExtrapolationMode::Repeat);` (scope `UE::Learning::FrameAttribute`) — Extract the phase for a given set of frame ranges, using the labeled events

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningFrameRangeSet.h` (Public)


#### struct `UE::Learning::FFrameRangeSet`  
`struct FFrameRangeSet`  
_L29-178_
- desc: A FFrameRangeSet represents a set of ranges within a set of sequences. This can be useful for encoding things like a collection of tags or labels for different parts of some database of animations, replays, or recordings. This data structure stores that information in a way that makes performing operations such as union, intersection, difference etc, efficient. The way it works is by storing a sorted array of "entries", where each entry has a corresponding sequence, the number of ranges in the set for that sequence, and an index into three large arrays of range starts, lengths, and offsets. The sub-ranges of the large arrays of range starts and lengths are also sorted, while the offsets arrays stores the offset that would be used if you had to take a slice of a large flat array of frame data. Having the entries sorted by sequence, and the ranges sorted, allows for efficient set operations via tape-merge algorithms. This data-structure is related to the FrameSet data-structure, which essentially acts the same way but stores individual frames instead of frame ranges.
- L34 _public prototype_ `void Check() const;` — Check if the FrameRangeSet is well-formed (i.e. correctly sorted without duplicate entries)
- L40 _public prototype_ `void AddEntry( const int32 InSequence, const TLearningArrayView<1, const int32> InStarts, const TLearningArrayView<1, const int32> InLengths);` — Adds the given ranges associated with the given sequence to the set. Assumes this sequence (and no sequences with a larger index) are already added to the set.
- L46 _public prototype_ `bool IsEmpty() const;` — True if the FrameRangeSet is Empty, otherwise false
- L49 _public prototype_ `void Empty();` — Empties the FrameRangeSet
- L52 _public prototype_ `int32 GetEntryNum() const;` — Gets the number of entries in the FrameRangeSet
- L55 _public prototype_ `TLearningArrayView<1, const int32> GetEntrySequences() const;` — Returns an array of sequences for each entry
- L58 _public prototype_ `TLearningArrayView<1, const int32> GetEntryRangeNums() const;` — Returns an array for the number of ranges in each entry
- L61 _public prototype_ `int32 GetEntrySequence(const int32 EntryIdx) const;` — Gets the sequence associated with a given entry
- L64 _public prototype_ `int32 GetEntryRangeNum(const int32 EntryIdx) const;` — Gets the number of ranges for a given entry
- L67 _public prototype_ `int32 GetEntryTotalFrameNum(const int32 EntryIdx) const;` — Computes the total number of frames given by all ranges in an entry
- L70 _public prototype_ `TLearningArrayView<1, const int32> GetEntryRangeStarts(const int32 EntryIdx) const;` — Gets all the range starts associated with a given entry
- L73 _public prototype_ `TLearningArrayView<1, const int32> GetEntryRangeLengths(const int32 EntryIdx) const;` — Gets all the range lengths associated with a given entry
- L76 _public prototype_ `TLearningArrayView<1, const int32> GetEntryRangeOffsets(const int32 EntryIdx) const;` — Gets all the range offsets associated with a given entry
- L79 _public prototype_ `int32 GetEntryRangeStart(const int32 EntryIdx, const int32 RangeIdx) const;` — Gets the range start associated with a given entry and range index
- L82 _public prototype_ `int32 GetEntryRangeLength(const int32 EntryIdx, const int32 RangeIdx) const;` — Gets the range length associated with a given entry and range index
- L85 _public prototype_ `int32 GetEntryRangeStop(const int32 EntryIdx, const int32 RangeIdx) const;` — Gets the range stop associated with a given entry and range index
- L88 _public prototype_ `int32 GetEntryRangeOffset(const int32 EntryIdx, const int32 RangeIdx) const;` — Computes the offset associated with a given entry and range index
- L91 _public prototype_ `float GetEntryRangeStartTime(const int32 EntryIdx, const int32 RangeIdx, const float FrameDeltaTime) const;` — Gets the range start time associated with a given entry and range index
- L94 _public prototype_ `float GetEntryRangeEndTime(const int32 EntryIdx, const int32 RangeIdx, const float FrameDeltaTime) const;` — Gets the range end time associated with a given entry and range index
- L97 _public prototype_ `float GetEntryRangeDuration(const int32 EntryIdx, const int32 RangeIdx, const float FrameDeltaTime) const;` — Gets the range duration associated with a given entry and range index
- L100 _public prototype_ `int32 GetTotalRangeNum() const;` — Computes the total number of ranges across all entries
- L103 _public prototype_ `TLearningArrayView<1, const int32> GetAllRangeStarts() const;` — Gets an array of the range starts for all ranges
- L106 _public prototype_ `TLearningArrayView<1, const int32> GetAllRangeLengths() const;` — Gets an array of the range lengths for all ranges
- L109 _public prototype_ `TLearningArrayView<1, const int32> GetAllRangeOffsets() const;` — Gets an array of the range offsets for all ranges
- L112 _public prototype_ `int32 GetTotalFrameNum() const;` — Computes the total number of frames across all entries and ranges
- L115 _public prototype_ `float GetAverageFrameNum() const;` — Computes the average number of frames across all entries and ranges
- L118 _public prototype_ `int32 GetMaxFrameNum() const;` — Gets the largest number of frames across all entries and ranges
- L121 _public prototype_ `int32 GetMinFrameNum() const;` — Gets the smallest number of frames across all entries and ranges
- L124 _public prototype_ `bool ContainsSequence(const int32 Sequence) const;` — Checks if this FrameRangeSet contains a given sequence
- L127 _public prototype_ `bool Contains(const int32 Sequence, const int32 Frame) const;` — Checks if this FrameRangeSet contains a given sequence and frame in that sequence
- L130 _public prototype_ `bool EntryContains(const int32 EntryIdx, const int32 Frame) const;` — Checks if the given Entry of this FrameRangeSet contains a frame
- L133 _public prototype_ `bool IntersectsRange(const int32 Sequence, const int32 Start, const int32 Length) const;` — Checks if this FrameRangeSet intersects a sequence and any part of a range in that sequence
- L136 _public prototype_ `bool EntryContainsRange(const int32 EntryIdx, const int32 Start, const int32 Length) const;` — Checks if the given Entry of this FrameRangeSet fully contains a range
- L139 _public prototype_ `bool EntryIntersectsRange(const int32 EntryIdx, const int32 Start, const int32 Length) const;` — Checks if the given Entry of this FrameRangeSet intersects any part of a range
- L142 _public prototype_ `bool ContainsTime(const int32 Sequence, const float Time, const float FrameDeltaTime, const float Tolerance = UE_KINDA_SMALL_NUMBER) const;` — Checks if this FrameRangeSet contains a given sequence and time in that sequence
- L145 _public prototype_ `int32 FindSequenceEntry(const int32 Sequence) const;` — Finds the entry index associated with a given sequence
- L148 _public prototype_ `bool Find(int32& OutEntryIdx, int32& OutRangeIdx, int32& OutRangeFrame, const int32 Sequence, const int32 Frame) const;` — Finds the entry index and range index associated with a given sequence and frame in that sequence
- L151 _public prototype_ `bool FindTotalRange(int32& OutEntryIdx, int32& OutRangeIdx, const int32 TotalRangeIdx) const;` — Finds the entry index and range index associated with a range index into all ranges
- L154 _public prototype_ `bool FindTime(int32& OutEntryIdx, int32& OutRangeIdx, float& OutRangeTime, const int32 Sequence, const float Time, const float FrameDeltaTime, const float Tolerance = UE_KINDA_SMALL_NUMBER) const;` — Finds the entry index and range index associated with a given sequence and time in that sequence
- L157 _public prototype_ `bool FindOffset(int32& OutEntryIdx, int32& OutRangeIdx, int32& OutRangeFrame, const int32 Offset) const;` — Finds entry index, frame index, and frame in that range, associated with some offset
- L162 _public member_ `TLearningArray<1, int32> EntrySequences;` — Array of sequences associated with each entry
- L165 _public member_ `TLearningArray<1, int32> EntryRangeOffsets;` — Array of offsets into the RangeStarts, RangeLengths, RangeOffsets arrays associated with each entry
- L168 _public member_ `TLearningArray<1, int32> EntryRangeNums;` — Array of the number of ranges associated with each entry
- L171 _public member_ `TLearningArray<1, int32> RangeStarts;` — Large array of all range starts for all entries, indexed using offsets from EntryRangeOffsets
- L174 _public member_ `TLearningArray<1, int32> RangeLengths;` — Large array of all range lengths for all entries, indexed using offsets from EntryRangeOffsets
- L177 _public member_ `TLearningArray<1, int32> RangeOffsets;` — Large array of all range frame offsets for all entries, indexed using offsets from EntryRangeOffsets

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEARNING_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Learning` (scope `UE`)
- L180 _namespace_ `namespace FrameRangeSet` (scope `UE::Learning`)
- L183 _prototype_ `bool Equal(const FFrameRangeSet& Lhs, const FFrameRangeSet& Rhs);` (scope `UE::Learning::FrameRangeSet`) — Checks if two frame range sets are equal
- L186 _prototype_ `void Union(FFrameRangeSet& OutFrameRangeSet, const FFrameSet& FrameSet, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameRangeSet`) — Computes the union of a frame set and frame range set
- L189 _prototype_ `void Intersection(FFrameSet& OutFrameSet, const FFrameSet& FrameSet, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameRangeSet`) — Computes the intersection of a frame set and frame range set
- L192 _prototype_ `void Difference(FFrameSet& OutFrameSet, const FFrameSet& FrameSet, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameRangeSet`) — Computes the difference of a frame set and frame range set
- L195 _prototype_ `void Difference(FFrameRangeSet& OutFrameRangeSet, const FFrameRangeSet& FrameRangeSet, const FFrameSet& FrameSet);` (scope `UE::Learning::FrameRangeSet`) — Computes the difference of a frame range set and a frame set
- L198 _prototype_ `void Union(FFrameRangeSet& Out, const FFrameRangeSet& Lhs, const FFrameRangeSet& Rhs);` (scope `UE::Learning::FrameRangeSet`) — Computes the union of two frame range sets
- L201 _prototype_ `void Intersection(FFrameRangeSet& Out, const FFrameRangeSet& Lhs, const FFrameRangeSet& Rhs);` (scope `UE::Learning::FrameRangeSet`) — Computes the intersection of two frame range sets
- L204 _prototype_ `void Difference(FFrameRangeSet& Out, const FFrameRangeSet& Lhs, const FFrameRangeSet& Rhs);` (scope `UE::Learning::FrameRangeSet`) — Computes the difference of two frame range sets
- L211 _prototype_ `int32 IntersectionWithOffsets( FFrameRangeSet& Out, TLearningArrayView<1, int32> OutLhsOffsets, TLearningArrayView<1, int32> OutRhsOffsets, const FFrameRangeSet& Lhs, const FFrameRangeSet& Rhs);` (scope `UE::Learning::FrameRangeSet`) — Computes the intersection of two frame range sets while recording the flat frame offsets in the lhs and rhs, associated with each range that gets added to the output. The OutLhsOffsets and OutRhsOffsets outputs should be pre-allocated to at least the maximum of the number of ranges in Lhs and Rhs. Returns the number of ranges in the added to the output frame range set.
- L219 _prototype_ `void Bounds(FFrameRangeSet& Out, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameRangeSet`) — Computes the bounding ranges of a given frame range set
- L222 _prototype_ `void Bounds(FFrameRangeSet& Out, const FFrameSet& FrameSet);` (scope `UE::Learning::FrameRangeSet`) — Computes the bounding ranges of a given frame set
- L225 _prototype_ `void Intersects(FFrameRangeSet& Out, const FFrameRangeSet& Lhs, const FFrameRangeSet& Rhs);` (scope `UE::Learning::FrameRangeSet`) — Computes all of the ranges in the Lhs which contain any part of the ranges in the Rhs
- L228 _prototype_ `void Intersects(FFrameRangeSet& Out, const FFrameRangeSet& Lhs, const FFrameSet& Rhs);` (scope `UE::Learning::FrameRangeSet`) — Computes all of the ranges in the Lhs which contain any part of the frames in the Rhs
- L231 _prototype_ `void TrimStart(FFrameRangeSet& Out, const FFrameRangeSet& FrameRangeSet, const int32 TrimFrameNum);` (scope `UE::Learning::FrameRangeSet`) — Creates a new frame range set with the start of all ranges trimmed by the given number of frames
- L234 _prototype_ `void TrimEnd(FFrameRangeSet& Out, const FFrameRangeSet& FrameRangeSet, const int32 TrimFrameNum);` (scope `UE::Learning::FrameRangeSet`) — Creates a new frame range set with the end of all ranges trimmed by the given number of frames
- L237 _prototype_ `void Trim(FFrameRangeSet& Out, const FFrameRangeSet& FrameRangeSet, const int32 TrimStartFrameNum, const int32 TrimEndFrameNum);` (scope `UE::Learning::FrameRangeSet`) — Creates a new frame range set with both the start and the end of all ranges trimmed by the given numbers of frames
- L240 _prototype_ `void PadStart(FFrameRangeSet& Out, const FFrameRangeSet& FrameRangeSet, const int32 PadFrameNum);` (scope `UE::Learning::FrameRangeSet`) — Creates a new frame range set with the start of all ranges padded by the given number of frames
- L243 _prototype_ `void PadEnd(FFrameRangeSet& Out, const FFrameRangeSet& FrameRangeSet, const int32 PadFrameNum);` (scope `UE::Learning::FrameRangeSet`) — Creates a new frame range set with the end of all ranges padded by the given number of frames
- L246 _prototype_ `void Pad(FFrameRangeSet& Out, const FFrameRangeSet& FrameRangeSet, const int32 PadStartFrameNum, int32 PadEndFrameNum);` (scope `UE::Learning::FrameRangeSet`) — Creates a new frame range set with both the start and the end of all ranges padded by the given numbers of frames
- L249 _prototype_ `void GatherRanges(FFrameRangeSet& Out, const FFrameRangeSet& FrameRangeSet, const FIndexSet Indices);` (scope `UE::Learning::FrameRangeSet`) — Creates a new frame range set with just the ranges given by the provided indices
- L252 _prototype_ `void MakeFromFrameSet(FFrameRangeSet& OutFrameRangeSet, const FFrameSet& FrameSet);` (scope `UE::Learning::FrameRangeSet`) — Makes a Frame Range Set consisting of single-frame ranges from a frame set
- L255 _prototype_ `void MakeFrameSetFromRangeStarts(FFrameSet& OutFrameSet, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameRangeSet`) — Create a frame set from all of the range starts of a given frame range set
- L258 _prototype_ `void MakeFrameSetFromRangeEnds(FFrameSet& OutFrameSet, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameRangeSet`) — Create a frame set from all of the range ends of a given frame range set
- L261 _prototype_ `void MakeFrameSetFromRangeInterval(FFrameSet& OutFrameSet, const FFrameRangeSet& FrameRangeSet, const int32 IntervalFrames = 10);` (scope `UE::Learning::FrameRangeSet`) — Create a frame set from a given frame range set, sampling frames at a regular interval
- L264 _prototype_ `void RangesBeforeFrameSet(FFrameRangeSet& OutFrameRangeSet, const FFrameRangeSet& FrameRangeSet, const FFrameSet& FrameSet);` (scope `UE::Learning::FrameRangeSet`) — Trim a frame range set to just the period of time before the first occurrence of a frame from a given frame set
- L267 _prototype_ `void RangesAfterFrameSet(FFrameRangeSet& OutFrameRangeSet, const FFrameRangeSet& FrameRangeSet, const FFrameSet& FrameSet);` (scope `UE::Learning::FrameRangeSet`) — Trim a frame range set to just the period of time after the first occurrence of a frame from a given frame set
- L270 _prototype_ `void AllRangeEntries( TLearningArrayView<1, int32> OutRangeEntries, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameRangeSet`) — Computes the entry indices associated with every range in the set
- L275 _prototype_ `void AllRangeIndices( TLearningArrayView<1, int32> OutRangeIndices, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameRangeSet`) — Computes the range indices associated with every range in the set
- L280 _prototype_ `void AllRangeSequences( TLearningArrayView<1, int32> OutRangeSequences, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::FrameRangeSet`) — Computes the sequences associated with every range in the set
- L285 _prototype_ `void AllRangeStartTimes( TLearningArrayView<1, float> OutRangeStartTimes, const FFrameRangeSet& FrameRangeSet, const float FrameDeltaTime);` (scope `UE::Learning::FrameRangeSet`) — Computes the start times associated with every range in the set
- L291 _prototype_ `void AllRangeEndTimes( TLearningArrayView<1, float> OutRangeEndTimes, const FFrameRangeSet& FrameRangeSet, const float FrameDeltaTime);` (scope `UE::Learning::FrameRangeSet`) — Computes the end times associated with every range in the set
- L297 _prototype_ `void AllRangeDurations( TLearningArrayView<1, float> OutRangeDurations, const FFrameRangeSet& FrameRangeSet, const float FrameDeltaTime);` (scope `UE::Learning::FrameRangeSet`) — Computes the durations associated with every range in the set
- L303 _prototype_ `void ForEachRange( const FFrameRangeSet& FrameRangeSet, const TFunctionRef<void( const int32 TotalRangeIdx, const int32 EntryIdx, const int32 RangeIdx)> Body);` (scope `UE::Learning::FrameRangeSet`) — Iterates over every range in the set and calls the provided callback
- L311 _prototype_ `void ParallelForEachRange( const FFrameRangeSet& FrameRangeSet, const TFunctionRef<void( const int32 TotalRangeIdx, const int32 EntryIdx, const int32 RangeIdx)> Body);` (scope `UE::Learning::FrameRangeSet`) — Iterates over every range in the set in parallel and calls the provided callback

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningFrameSet.h` (Public)


#### struct `UE::Learning::FFrameSet`  
`struct FFrameSet`  
_L29-125_
- desc: A FrameSet represents a set of frames within a set of sequences. This can be useful for encoding things like a collection of single-frame events. This data structure stores that information in a way that makes performing operations such as union, intersection, difference etc, efficient. The way it works is by storing a sorted array of "entries", where each entry has a corresponding sequence, the number of frames in the set for that sequence, and an offset into a large array of frames. The sub-ranges of the large array of frames corresponding to each entry is also sorted. Having the entries sorted by sequence, and the frames sorted, allows for efficient set operations via tape-merge algorithms. Also provided are some algorithms for getting "offsets", which correspond to the index associated with a particular thing if you were to flatten this data-structure into one large array of frames. This data-structure is related to the FrameRangeSet data-structure, which essentially acts the same way but stores frame ranges instead of individual frames.
- L34 _public prototype_ `void Check() const;` — Check if the FrameSet is well-formed (i.e. correctly sorted without duplicate entries)
- L40 _public prototype_ `void AddEntry( const int32 InSequence, const TLearningArrayView<1, const int32> InFrames);` — Adds the given frames associated with the given sequence to the set. Assumes this sequence (and no sequences with a larger index) are already added to the set.
- L45 _public prototype_ `bool IsEmpty() const;` — True if the FrameSet is Empty, otherwise false
- L48 _public prototype_ `void Empty();` — Empties the FrameSet
- L51 _public prototype_ `int32 GetEntryNum() const;` — Gets the number of entries in the FrameSet
- L54 _public prototype_ `TLearningArrayView<1, const int32> GetEntrySequences() const;` — Returns and array of sequences corresponding to each entry
- L57 _public prototype_ `TLearningArrayView<1, const int32> GetEntryFrameNums() const;` — Returns an array containing the number of frames corresponding in each entry
- L60 _public prototype_ `int32 GetEntrySequence(const int32 EntryIdx) const;` — Gets the sequence associated with a given entry
- L63 _public prototype_ `int32 GetEntryFrameNum(const int32 EntryIdx) const;` — Gets the number of frames for a given entry
- L66 _public prototype_ `TLearningArrayView<1, const int32> GetEntryFrames(const int32 EntryIdx) const;` — Gets the array of frames associated with a given entry
- L69 _public prototype_ `int32 GetEntryFrame(const int32 EntryIdx, const int32 FrameIdx) const;` — Gets the frame number for an entry and entry frame index
- L72 _public prototype_ `float GetEntryFrameTime(const int32 EntryIdx, const int32 FrameIdx, const float FrameDeltaTime) const;` — Gets the frame time associated with an entry and entry frame index
- L75 _public prototype_ `int32 GetEntryOffset(const int32 EntryIdx) const;` — Gets the flat offset associated with a particular entry if you were to flatten this data structure
- L78 _public prototype_ `TLearningArrayView<1, const int32> GetAllFrames() const;` — Gets an array of the frames
- L81 _public prototype_ `int32 GetTotalFrameNum() const;` — Gets the total number of frames if you were to flatten this data structure
- L84 _public prototype_ `bool ContainsSequence(const int32 Sequence) const;` — Checks if this FrameSet contains a given sequence
- L87 _public prototype_ `bool Contains(const int32 Sequence, const int32 Frame) const;` — Checks if this FrameSet contains a given sequence and frame in that sequence
- L90 _public prototype_ `int32 FindSequenceEntry(const int32 Sequence) const;` — Finds the entry index associated with a given sequence
- L93 _public prototype_ `bool Find(int32& OutEntryIdx, int32& OutFrameIdx, const int32 Sequence, const int32 Frame) const;` — Finds the entry index and frame index associated with a given sequence and frame in that sequence
- L96 _public prototype_ `bool FindNearest(int32& OutEntryIdx, int32& OutFrameIdx, int32& OutFrameDifference, const int32 Sequence, const int32 Frame) const;` — Finds the nearest entry index, frame index, and the frame difference, for some given sequence and frame in that sequence
- L102 _public prototype_ `bool FindNearestInRange( int32& OutEntryIdx, int32& OutFrameIdx, int32& OutFrameDifference, const int32 Sequence, const int32 Frame, const int32 RangeStart, const int32 RangeLength) const;` — Finds the nearest entry index, frame index, and the frame difference, for some given sequence and frame in that sequence, limited to a given range
- L107 _public prototype_ `bool FindOffset(int32& OutEntryIdx, int32& OutFrameIdx, const int32 Offset) const;` — Finds entry index and frame index associated with some flat offset
- L110 _public prototype_ `bool FindFramesInRange(int32& OutStartFrameIdx, int32& OutFrameNum, const int32 EntryIdx, const int32 RangeStart, const int32 RangeLength) const;` — Finds all the frames within the given range, returning the first frame index and the number of frames
- L115 _public member_ `TLearningArray<1, int32> EntrySequences;` — Array of sequences associated with each entry
- L118 _public member_ `TLearningArray<1, int32> EntryFrameOffsets;` — Array of offsets into the Frames array associated with each entry
- L121 _public member_ `TLearningArray<1, int32> EntryFrameNums;` — Array of the number of frames associated with each entry
- L124 _public member_ `TLearningArray<1, int32> Frames;` — Large array of all frames for all entries, indexed using offsets from EntryFrameOffsets

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEARNING_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Learning` (scope `UE`)
- L127 _namespace_ `namespace FrameSet` (scope `UE::Learning`)
- L130 _prototype_ `bool Equal(const FFrameSet& Lhs, const FFrameSet& Rhs);` (scope `UE::Learning::FrameSet`) — Checks if two frame sets are equal
- L133 _prototype_ `void Union(FFrameSet& Out, const FFrameSet& Lhs, const FFrameSet& Rhs);` (scope `UE::Learning::FrameSet`) — Computes the union of two frame sets
- L136 _prototype_ `void Intersection(FFrameSet& Out, const FFrameSet& Lhs, const FFrameSet& Rhs);` (scope `UE::Learning::FrameSet`) — Computes the intersection of two frame sets
- L139 _prototype_ `void Difference(FFrameSet& Out, const FFrameSet& Lhs, const FFrameSet& Rhs);` (scope `UE::Learning::FrameSet`) — Computes the difference of two frame sets
- L142 _prototype_ `void AllFrameEntries( TLearningArrayView<1, int32> OutFrameEntries, const FFrameSet& FrameSet);` (scope `UE::Learning::FrameSet`) — Computes the entry indices associated with every frame in the set
- L147 _prototype_ `void AllFrameIndices( TLearningArrayView<1, int32> OutFrameIndices, const FFrameSet& FrameSet);` (scope `UE::Learning::FrameSet`) — Computes the frame indices associated with every frame in the set
- L152 _prototype_ `void AllFrameSequences( TLearningArrayView<1, int32> OutFrameSequences, const FFrameSet& FrameSet);` (scope `UE::Learning::FrameSet`) — Computes the sequences associated with every frame in the set
- L157 _prototype_ `void AllFrameTimes( TLearningArrayView<1, float> OutFrameTimes, const FFrameSet& FrameSet, const float FrameDeltaTime);` (scope `UE::Learning::FrameSet`) — Computes the times associated with every frame in the set
- L163 _prototype_ `void ForEachFrame( const FFrameSet& FrameSet, const TFunctionRef<void( const int32 TotalFrameIdx, const int32 EntryIdx, const int32 FrameIdx)> Body);` (scope `UE::Learning::FrameSet`) — Iterates over every frame in the set and calls the provided callback
- L171 _prototype_ `void ParallelForEachFrame( const FFrameSet& FrameSet, const TFunctionRef<void( const int32 TotalFrameIdx, const int32 EntryIdx, const int32 RangeIdx)> Body);` (scope `UE::Learning::FrameSet`) — Iterates over every frame in the set in parallel and calls the provided callback

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningKMeans.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEARNING_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Learning` (scope `UE`)
- L9 _namespace_ `namespace KMeans` (scope `UE::Learning`)
- L20 _prototype_ `void InitCenters( TLearningArrayView<2, float> OutCenters, const TLearningArrayView<2, const float> Samples, const uint32 Seed);` (scope `UE::Learning::KMeans`) — Initialize a set of KMean Cluster centers by taking random points from a set of samples @param Centers			Output cluster centers of shape (ClusterNum, DimensionNum) @param Samples			Samples to be clustered of shape (SamplesNum, DimensionNum) @param Seed				Random Seed
- L34 _prototype_ `void UpdateAssignmentsFromCenters( TLearningArrayView<1, int32> OutAssignments, const TLearningArrayView<2, const float> Centers, const TLearningArrayView<2, const float> Samples, const bool bParallelEvaluation = true, const uint16 MinParallelBatchSize = 16);` (scope `UE::Learning::KMeans`) — Updates the assignments of each sample to each cluster @param OutAssignments			For each sample, the index of the cluster it is assigned to - shape (SamplesNum) @param Centers				Cluster centers of shape (ClusterNum, DimensionNum) @param Samples				Samples to be clustered of shape (SamplesNum, DimensionNum) @param bParallelEvaluation	If to allow for multi-threaded evaluation @param MinParallelBatchSize	Minimum batch size to use for multi-threaded evaluation
- L47 _prototype_ `void CountClusterAssignments( TLearningArrayView<1, int32> OutAssignmentCounts, const TLearningArrayView<1, const int32> Assignments);` (scope `UE::Learning::KMeans`) — Counters the number of assignments in each cluster @param OutAssignmentCounts	Number of samples assigned to each cluster - shape (ClusterNum) @param Assignments			Index of the cluster assigned to each sample - shape (SamplesNum
- L59 _prototype_ `void UpdateCenters( TLearningArrayView<2, float> OutCenters, const TLearningArrayView<1, const int32> Assignments, const TLearningArrayView<1, const int32> AssignmentCounts, const TLearningArrayView<2, const float> Samples);` (scope `UE::Learning::KMeans`) — Updates the cluster centers based on the samples and their assignments @param OutCenters			New cluster centers of shape (ClusterNum, DimensionNum) @param Assignments		Index of the cluster assigned to each sample - shape (SamplesNum) @param AssignmentCounts	Number of samples assigned to each cluster - shape (ClusterNum) @param Samples			Samples to be clustered of shape (SamplesNum, DimensionNum)
- L74 _prototype_ `void InitBounds( TLearningArrayView<2, float> OutMins, TLearningArrayView<2, float> OutMaxs, const TLearningArrayView<2, const float> Samples, const uint32 Seed);` (scope `UE::Learning::KMeans`) — Initialize a set of KMean Cluster bounds by taking random points from a set of samples @param OutMins			Output cluster mins of shape (ClusterNum, DimensionNum) @param OutMaxs			Output cluster maxs of shape (ClusterNum, DimensionNum) @param Samples			Samples to be clustered of shape (SamplesNum, DimensionNum) @param Seed				Random Seed
- L90 _prototype_ `void UpdateAssignmentsFromBounds( TLearningArrayView<1, int32> OutAssignments, const TLearningArrayView<2, const float> Mins, const TLearningArrayView<2, const float> Maxs, const TLearningArrayView<2, const float> Samples, const bool bParallelEvaluation = true, const uint16 MinParallelBatchSize = 16);` (scope `UE::Learning::KMeans`) — Updates the assignments of each sample to each cluster @param OutAssignments			For each sample, the index of the cluster it is assigned to - shape (SamplesNum) @param Mins					Cluster mins of shape (ClusterNum, DimensionNum) @param Maxs					Cluster maxs of shape (ClusterNum, DimensionNum) @param Samples				Samples to be clustered of shape (SamplesNum, DimensionNum) @param bParallelEvaluation	If to allow for multi-threaded evaluation @param MinParallelBatchSize	Minimum batch size to use for multi-threaded evaluation
- L107 _prototype_ `void UpdateBounds( TLearningArrayView<2, float> OutMins, TLearningArrayView<2, float> OutMaxs, const TLearningArrayView<1, const int32> Assignments, const TLearningArrayView<2, const float> Samples);` (scope `UE::Learning::KMeans`) — Updates the cluster bounds based on the samples and their assignments @param OutMins			New cluster mins of shape (ClusterNum, DimensionNum) @param OutMaxs			New cluster maxs of shape (ClusterNum, DimensionNum) @param Assignments		Index of the cluster assigned to each sample - shape (SamplesNum) @param AssignmentCounts	Number of samples assigned to each cluster - shape (ClusterNum) @param Samples			Samples to be clustered of shape (SamplesNum, DimensionNum)
- L125 _prototype_ `void ComputeClusteredIndex( TLearningArrayView<2, float> OutClusteredSamples, TLearningArrayView<1, int32> OutClusterStarts, TLearningArrayView<1, int32> OutClusterLengths, TLearningArrayView<1, int32> OutSampleMapping, TLearningArrayView<1, int32> OutInverseSampleMapping, const TLearningArrayView<1, const int32> Assignments, const TLearningArrayView<1, const int32> AssignmentCounts, const TLearningArrayView<2, const float> Samples);` (scope `UE::Learning::KMeans`) — Generates an array of samples points, re-ordered and grouped into their clusters @param OutClusteredSamples		Array of samples, grouped into their clusters of shape (SamplesNum, DimensionNum) @param OutClusterStarts			Start index into OutClusteredSamples for each cluster of shape (ClusterNum) @param OutClusterLengths			Number of samples in each cluster of shape (ClusterNum) @param OutSampleMapping			Index mapping into OutClusteredSamples for each sample in the original array - shape (SamplesNum) @param OutInverseSampleMapping	Index mapping from OutClusteredSamples into the original array for each sample - shape (SamplesNum) @param Assignments				Index of the cluster assigned to each sample - shape (SamplesNum) @param AssignmentCounts			Number of samples assigned to each cluster - shape (ClusterNum) @param Samples					Samples to be clustered of shape (SamplesNum, DimensionNum)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningLog.h` (Public)


#### enum `UE::Learning::ELogSetting`  
`enum class ELogSetting : uint8`  
_L14-21_
- desc: Log Settings
- L17 _public enumerator_ `Normal` — Logs basic information
- L20 _public enumerator_ `Silent` — No logging

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEARNING_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Learning` (scope `UE`)
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLearning, Log, All);`

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningNeuralNetwork.h` (Public)


#### class `ULearningNeuralNetworkData`  
`class ULearningNeuralNetworkData : public UObject`  
_L38-129_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Neural Network Data Object This is the UObject which contains the actual data used by a Neural Network. It stores the raw FileData used to construct the network using NNE, as well as the input and output sizes and a compatibility hash that can be used to quickly check if two networks may be compatible in terms of inputs and outputs. Internally this also stores the various things required to map between NNE style inference and the style of inference used in Learning via FNeuralNetwork and FNeuralNetworkInference.
- L45 _public prototype_ `TSharedPtr<UE::Learning::FNeuralNetwork>& GetNetwork();` — Get the FNeuralNetwork object that can be used to do inference.
- L55 _public prototype_ `void Init( const int32 InInputSize, const int32 InOutputSize, const int32 InCompatibilityHash, const TArrayView<const uint8> InFileData);` — Initialize the ULearningNeuralNetworkData object given some input and output sizes as well as a compatibility hash and FileData. @param InInputSize			Network Input Size @param InOutputSize			Network Output Size @param InCompatibilityHash	Compatibility Hash @param InFileData			Network FileData
- L62 _public prototype_ `void InitFrom(const ULearningNeuralNetworkData* OtherNetworkData);` — Initialize this network from another ULearningNeuralNetworkData object
- L65 _public prototype_ `bool LoadFromSnapshot(const TArrayView<const uint8> InBytes);` — Load a snapshot of this network from the given array of bytes
- L68 _public prototype_ `void SaveToSnapshot(TArrayView<uint8> OutBytes) const;` — Save a snapshot of this network to the given array of bytes
- L71 _public prototype_ `int32 GetSnapshotByteNum() const;` — Number of bytes required to save or load a snapshot of this network
- L74 _public prototype_ `bool IsEmpty() const;` — If this network is empty or not
- L77 _public prototype_ `int32 GetInputSize() const;` — Gets the network input size
- L80 _public prototype_ `int32 GetOutputSize() const;` — Gets the network output size
- L83 _public prototype_ `int32 GetCompatibilityHash() const;` — Gets the compatibility hash
- L86 _public prototype_ `int32 GetContentHash() const;` — Gets the content hash
- L89 _public prototype_ `int32 GetUpdateNumber() const;` — Gets the update number which is incremented each time the network is loaded from a snapshot
- L94 _private prototype_ `virtual void PostLoad() override final;` — Calls UpdateNetwork to update the internal representation.
- L97 _private prototype_ `void UpdateNetwork();` — Uploads the FileData to NNE and updates the internal in-memory representation of the network used for inference.
- L101 _private member_ `int32 InputSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Network Properties")` — Size of the inputs expected by this network
- L105 _private member_ `int32 OutputSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Network Properties")` — Size of the output produced by this network
- L109 _private member_ `int32 CompatibilityHash = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Network Properties")` — Compatibility hash used for testing if inputs to one network are compatible with another
- L113 _private member_ `int32 ContentHash = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Network Properties")` — Content hash which can be used to see when the network data has changed
- L117 _private member_ `TArray<uint8> FileData;` — `UPROPERTY()` — File data used by NNE
- L121 _private member_ `int32 UpdateNumber = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Network Properties")` — Number which is incremented each time the network is loaded from a snapshot
- L125 _private member_ `TObjectPtr<UNNEModelData> ModelData;` — `UPROPERTY()` — Model Data used by NNE
- L128 _private member_ `TSharedPtr<UE::Learning::FNeuralNetwork> Network;` — Internal in-memory network representation

#### struct `UE::Learning::FNeuralNetworkInferenceSettings`  
`struct FNeuralNetworkInferenceSettings`  
_L136-143_
- desc: Settings object for a neural network instance
- L139 _public member_ `bool bParallelEvaluation = true;` — If to allow for multi-threaded evaluation
- L142 _public member_ `uint16 MinParallelBatchSize = 16;` — Minimum batch size to use for multi-threaded evaluation

#### struct `UE::Learning::FNeuralNetwork`  
`struct FNeuralNetwork`  
_L148-168_
- desc: Neural Network Object
- L151 _public prototype_ `TSharedRef<FNeuralNetworkInference> CreateInferenceObject( const int32 MaxBatchSize, const FNeuralNetworkInferenceSettings& Settings = FNeuralNetworkInferenceSettings());` — Create a new inference object for this network with the given maximum batch size and inference settings.
- L155 _public prototype_ `bool IsEmpty() const;`
- L156 _public prototype_ `int32 GetInputSize() const;`
- L157 _public prototype_ `int32 GetOutputSize() const;`
- L159 _public prototype_ `void UpdateModel(const TSharedPtr<NNE::IModelCPU>& InModel, const int32 InInputSize, const int32 InOutputSize);`
- L163 _private member_ `int32 InputSize = 0;`
- L164 _private member_ `int32 OutputSize = 0;`
- L165 _private member_ `TSharedPtr<NNE::IModelCPU> Model;`
- L166 _private member_ `TArray<TWeakPtr<FNeuralNetworkInference>, TInlineAllocator<64>> InferenceObjects;`
- L167 _private member_ `FRWLock Lock;`

#### struct `UE::Learning::FNeuralNetworkInference`  
`struct FNeuralNetworkInference`  
_L173-214_
- desc: Neural Network Inference Object
- L185 _public prototype_ `FNeuralNetworkInference( UE::NNE::IModelCPU& InModel, const int32 InMaxBatchSize, const int32 InInputSize, const int32 InOutputSize, const FNeuralNetworkInferenceSettings& InSettings = FNeuralNetworkInferenceSettings());` — Constructs a new network inference object. Generally this should not be called directly and FNeuralNetwork::CreateInferenceObject should be used instead so that created instances are tracked. @param InModel			NNE Model @param InMaxBatchSize	Maximum batch size @param InInputSize		Network input size @param InOutputSize		Network output size @param InSettings		Inference settings
- L198 _public prototype_ `void Evaluate(TLearningArrayView<2, float> Output, const TLearningArrayView<2, const float> Input);` — Evaluate this network. @param Output		The Output Buffer of shape (<= MaxBatchSize, OutputSize) @param Input			The Input Buffer of shape (<= MaxBatchSize, InputSize)
- L201 _public prototype_ `void ReloadModelInstances(NNE::IModelCPU& Model, const int32 InInputSize, const int32 InOutputSize);` — This function will re-build the internal Model Instances used for multi-threading. It should be called whenever the given Model is updated.
- L203 _public prototype_ `int32 GetMaxBatchSize() const;`
- L204 _public prototype_ `int32 GetInputSize() const;`
- L205 _public prototype_ `int32 GetOutputSize() const;`
- L209 _private member_ `int32 MaxBatchSize = 0;`
- L210 _private member_ `int32 InputSize = 0;`
- L211 _private member_ `int32 OutputSize = 0;`
- L212 _private member_ `FNeuralNetworkInferenceSettings Settings;`
- L213 _private member_ `TArray<TSharedPtr<NNE::IModelInstanceCPU>, TInlineAllocator<64>> ModelInstances;`

#### struct `UE::Learning::FNeuralNetworkFunction`  
`struct FNeuralNetworkFunction`  
_L219-264_
- desc: Neural-network based function object.
- L228 _public prototype_ `FNeuralNetworkFunction( const int32 InMaxInstanceNum, const TSharedPtr<FNeuralNetwork>& InNeuralNetwork, const FNeuralNetworkInferenceSettings& InInferenceSettings = FNeuralNetworkInferenceSettings());` — Constructs a Neural Network Function from the given Neural Network @param InMaxInstanceNum		Maximum number of instances to evaluate for @param InNeuralNetwork		Neural network to use @param InInferenceSettings	Inference settings
- L244 _public prototype_ `void Evaluate( TLearningArrayView<2, float> Output, const TLearningArrayView<2, const float> Input, const FIndexSet Instances);` — Evaluate this network for the given instances. Note: this function takes a lock, so although it can be called from multiple threads if the set of Instances don't overlap, it will not benefit from multi-threading. This is because to use the NNE interface all the instances that need to be evaluated must be gathered and scattered into internal buffers. @param Output		The Output Buffer of shape (<= MaxInstanceNum, OutputSize) @param Input			The Input Buffer of shape (<= MaxInstanceNum, InputSize) @param Instances		The instances to evaluate
- L250 _public prototype_ `void UpdateNeuralNetwork(const TSharedPtr<FNeuralNetwork>& NewNeuralNetwork);` — Sets the NeuralNetwork and re-creates the NeuralNetworkInference object.
- L253 _public prototype_ `const TSharedPtr<FNeuralNetwork>& GetNeuralNetwork() const;` — Gets the NeuralNetwork associated with this function
- L257 _private member_ `int32 MaxInstanceNum = 0;`
- L258 _private member_ `FRWLock EvaluationLock;`
- L259 _private member_ `TLearningArray<2, float> InputBuffer;`
- L260 _private member_ `TLearningArray<2, float> OutputBuffer;`
- L261 _private member_ `TSharedPtr<FNeuralNetwork> NeuralNetwork;`
- L262 _private member_ `TSharedPtr<FNeuralNetworkInference> NeuralNetworkInference;`
- L263 _private member_ `FNeuralNetworkInferenceSettings InferenceSettings;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LEARNING_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace NNE` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Learning` (scope `UE`)
- L131 _namespace_ `namespace UE`
- L131 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningObservation.h` (Public)


#### enum `UE::Learning::Observation::EType`  
`enum class EType : uint8`  
_L24-73_
- desc: Observation Type The core type of an observation object for which different encoding methods are defined.
- L27 _public enumerator_ `Null = 0` — Empty Observation
- L30 _public enumerator_ `Continuous = 1` — Vector of continuous float observations
- L33 _public enumerator_ `DiscreteExclusive = 2` — Set of exclusive discrete observations
- L36 _public enumerator_ `DiscreteInclusive = 3` — Set of inclusive discrete observations
- L39 _public enumerator_ `NamedDiscreteExclusive = 4` — Set of named exclusive discrete observations
- L42 _public enumerator_ `NamedDiscreteInclusive = 5` — Set of named inclusive discrete observations
- L45 _public enumerator_ `And = 6` — Combination of multiple observations
- L48 _public enumerator_ `OrExclusive = 7` — Exclusive choice from a set of observations
- L51 _public enumerator_ `OrInclusive = 8` — Inclusive choice from a set of observations
- L54 _public enumerator_ `Array = 9` — Fixed sized array of observations
- L57 _public enumerator_ `Set = 10` — Variable sized, unordered set of observations
- L60 _public enumerator_ `Encoding = 11` — Encoding of another observation
- L63 _public enumerator_ `Conv1d = 12` — 1d convolution of another observation
- L66 _public enumerator_ `Conv2d = 13` — 2d convolution of another observation
- L69 _public enumerator_ `Sparse = 14` — Sparse continuous observation indexed by integers
- L72 _public enumerator_ `NamedSparse = 15` — Sparse continuous observation indexed by names

#### enum `UE::Learning::Observation::ENormalization`  
`enum class ENormalization : uint8`  
_L75-81_
- L77 _public enumerator_ `Manual = 0`
- L78 _public enumerator_ `AutoShared = 1`
- L79 _public enumerator_ `AutoPerDimension = 2`
- L80 _public enumerator_ `AutoDimensionAverage = 3`

#### struct `UE::Learning::Observation::FSchemaElement`  
`struct FSchemaElement`  
_L101-101_
- desc: Observation Schema Element A single element in the observation schema representing a part of an observation. Internally this consists of a index used by the schema to look up the associated observation data and a generation id which can be used to check when this index is no longer valid.
- L101 _public member_ `struct FSchemaElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Observation Schema Element A single element in the observation schema representing a part of an observation. Internally this consists of a index used by the schema to look up the associated observation data and a generation id which can be used to check when this index is no longer valid.
- L101 _public member_ `struct FSchemaElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Observation Schema Element A single element in the observation schema representing a part of an observation. Internally this consists of a index used by the schema to look up the associated observation data and a generation id which can be used to check when this index is no longer valid.

#### struct `UE::Learning::Observation::FSchemaContinuousParameters`  
`struct FSchemaContinuousParameters`  
_L103-116_
- L106 _public member_ `int32 Num = 0;` — Number of values in the continuous observation
- L109 _public member_ `TArrayView<const float> Scales;` — Per-element standard deviation values for normalization. If empty, identity scaling is applied. *Only used when normalization option is set to manual.
- L112 _public member_ `TArrayView<const float> Offsets;` — Per-element mean values for normalization. If empty, zero bias is applied. *Only used when normalization option is set to manual.
- L115 _public member_ `ENormalization NormalizationOption = ENormalization::Manual;` — The normalization option to use

#### struct `UE::Learning::Observation::FSchemaDiscreteExclusiveParameters`  
`struct FSchemaDiscreteExclusiveParameters`  
_L118-122_
- L121 _public member_ `int32 Num = 0;` — Number of values in the discrete observation

#### struct `UE::Learning::Observation::FSchemaDiscreteInclusiveParameters`  
`struct FSchemaDiscreteInclusiveParameters`  
_L124-128_
- L127 _public member_ `int32 Num = 0;` — Number of values in the discrete observation

#### struct `UE::Learning::Observation::FSchemaNamedDiscreteExclusiveParameters`  
`struct FSchemaNamedDiscreteExclusiveParameters`  
_L130-134_
- L133 _public member_ `TArrayView<const FName> ElementNames;` — Names of the discrete observations.

#### struct `UE::Learning::Observation::FSchemaNamedDiscreteInclusiveParameters`  
`struct FSchemaNamedDiscreteInclusiveParameters`  
_L136-140_
- L139 _public member_ `TArrayView<const FName> ElementNames;` — Names of the discrete observations.

#### struct `UE::Learning::Observation::FSchemaAndParameters`  
`struct FSchemaAndParameters`  
_L142-149_
- L145 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sub-observations.
- L148 _public member_ `TArrayView<const FSchemaElement> Elements;` — The associated sub-observations.

#### struct `UE::Learning::Observation::FSchemaOrExclusiveParameters`  
`struct FSchemaOrExclusiveParameters`  
_L151-161_
- L154 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sub-observations.
- L157 _public member_ `TArrayView<const FSchemaElement> Elements;` — The associated sub-observations.
- L160 _public member_ `int32 EncodingSize = 128;` — The size of the encoding to use to combine these sub-observations.

#### struct `UE::Learning::Observation::FSchemaOrInclusiveParameters`  
`struct FSchemaOrInclusiveParameters`  
_L163-179_
- L166 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sub-observations.
- L169 _public member_ `TArrayView<const FSchemaElement> Elements;` — The associated sub-observations.
- L172 _public member_ `int32 AttentionEncodingSize = 16;` — The size of the attention embedding to use (per-attention-head) for sub-observations
- L175 _public member_ `int32 AttentionHeadNum = 4;` — The number of attention heads to use for combining sub-observations
- L178 _public member_ `int32 ValueEncodingSize = 32;` — The size of the output encoding to use (per-attention-head) for sub-observations

#### struct `UE::Learning::Observation::FSchemaArrayParameters`  
`struct FSchemaArrayParameters`  
_L181-188_
- L184 _public member_ `FSchemaElement Element;` — The array sub-element.
- L187 _public member_ `int32 Num = 0;` — The number of elements in the array.

#### struct `UE::Learning::Observation::FSchemaSetParameters`  
`struct FSchemaSetParameters`  
_L190-206_
- L193 _public member_ `FSchemaElement Element;` — The set sub-element.
- L196 _public member_ `int32 MaxNum = 0;` — The maximum number of elements in the set.
- L199 _public member_ `int32 AttentionEncodingSize = 16;` — The size of the attention embedding to use (per-attention-head) for sub-observations
- L202 _public member_ `int32 AttentionHeadNum = 4;` — The number of attention heads to use for combining sub-observations
- L205 _public member_ `int32 ValueEncodingSize = 32;` — The size of the output encoding to use (per-attention-head) for sub-observations

#### enum `UE::Learning::Observation::EEncodingActivationFunction`  
`enum class EEncodingActivationFunction : uint8`  
_L209-215_
- desc: Activation Function to use for encoding
- L211 _public enumerator_ `ELU = 0`
- L212 _public enumerator_ `ReLU = 1`
- L213 _public enumerator_ `TanH = 2`
- L214 _public enumerator_ `GELU = 3`

#### struct `UE::Learning::Observation::FSchemaEncodingParameters`  
`struct FSchemaEncodingParameters`  
_L217-230_
- L220 _public member_ `FSchemaElement Element;` — The sub-element.
- L223 _public member_ `int32 EncodingSize = 32;` — The size at which the sub-element should be encoded.
- L226 _public member_ `int32 LayerNum = 1;` — The number of layers in the encoding
- L229 _public member_ `EEncodingActivationFunction ActivationFunction = EEncodingActivationFunction::ELU;` — The activation function to use for encoding

#### enum `UE::Learning::Observation::EPaddingMode`  
`enum class EPaddingMode : uint8`  
_L233-237_
- desc: Enum of Padding Mode
- L235 _public enumerator_ `Zeros = 0`
- L236 _public enumerator_ `Circular = 1`

#### struct `UE::Learning::Observation::FSchemaConv1dParameters`  
`struct FSchemaConv1dParameters`  
_L239-264_
- L242 _public member_ `FSchemaElement Element;` — The sub-element.
- L245 _public member_ `int32 InputLength = 0;` — Length of the 1d convolution input.
- L248 _public member_ `int32 InChannels = 0;` — Number of input channels.
- L251 _public member_ `int32 OutChannels = 0;` — Number of output channels after convolution.
- L254 _public member_ `int32 KernelSize = 3;` — Size of the convolving kernel.
- L257 _public member_ `int32 Padding = 1;` — The amount of padding to add to both sides of the input.
- L260 _public member_ `EPaddingMode PaddingMode = EPaddingMode::Zeros;` — Zeros or Circular.
- L263 _public member_ `EEncodingActivationFunction ActivationFunction = EEncodingActivationFunction::ReLU;` — The activation function to use for the convolution layer.

#### struct `UE::Learning::Observation::FSchemaConv2dParameters`  
`struct FSchemaConv2dParameters`  
_L266-297_
- L269 _public member_ `FSchemaElement Element;` — The sub-element.
- L272 _public member_ `int32 InputHeight = 0;` — Height of the 2d convolution input.
- L275 _public member_ `int32 InputWidth = 0;` — Width of the 2d convolution input.
- L278 _public member_ `int32 InChannels = 0;` — Number of input channels.
- L281 _public member_ `int32 OutChannels = 0;` — Number of output channels after convolution.
- L284 _public member_ `int32 KernelSize = 3;` — Size of the convolving kernel.
- L287 _public member_ `int32 Stride = 1;` — Size of the convolution stride.
- L290 _public member_ `int32 Padding = 1;` — The amount of padding to add to both sides of the input.
- L293 _public member_ `EPaddingMode PaddingMode = EPaddingMode::Zeros;` — Zeros or Circular.
- L296 _public member_ `EEncodingActivationFunction ActivationFunction = EEncodingActivationFunction::ReLU;` — The activation function to use for the convolution layer.

#### struct `UE::Learning::Observation::FSchemaSparseParameters`  
`struct FSchemaSparseParameters`  
_L299-303_
- L302 _public member_ `int32 Num = 0;` — Number of values in the sparse observation

#### struct `UE::Learning::Observation::FSchemaNamedSparseParameters`  
`struct FSchemaNamedSparseParameters`  
_L305-309_
- L308 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sparse observation elements.

#### struct `UE::Learning::Observation::FSchema`  
`struct FSchema`  
_L318-536_
- desc: Observation Schema This object allows you to construct a description of the kind of observations you might want to provide as input to a policy. Internally this object contains a pool of individual elements. This allows them to be constructed performantly and in a cache efficient way. This object is therefore required to access any data about the individual observation elements that are created.
- L320 _public prototype_ `FSchemaElement CreateNull(const FName Tag = NAME_None);`
- L321 _public prototype_ `FSchemaElement CreateContinuous(const FSchemaContinuousParameters Parameters, const FName Tag = NAME_None);`
- L322 _public prototype_ `FSchemaElement CreateDiscreteExclusive(const FSchemaDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L323 _public prototype_ `FSchemaElement CreateDiscreteInclusive(const FSchemaDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L324 _public prototype_ `FSchemaElement CreateNamedDiscreteExclusive(const FSchemaNamedDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L325 _public prototype_ `FSchemaElement CreateNamedDiscreteInclusive(const FSchemaNamedDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L326 _public prototype_ `FSchemaElement CreateAnd(const FSchemaAndParameters Parameters, const FName Tag = NAME_None);`
- L327 _public prototype_ `FSchemaElement CreateOrExclusive(const FSchemaOrExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L328 _public prototype_ `FSchemaElement CreateOrInclusive(const FSchemaOrInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L329 _public prototype_ `FSchemaElement CreateArray(const FSchemaArrayParameters Parameters, const FName Tag = NAME_None);`
- L330 _public prototype_ `FSchemaElement CreateSet(const FSchemaSetParameters Parameters, const FName Tag = NAME_None);`
- L331 _public prototype_ `FSchemaElement CreateEncoding(const FSchemaEncodingParameters Parameters, const FName Tag = NAME_None);`
- L332 _public prototype_ `FSchemaElement CreateConv1d(const FSchemaConv1dParameters Parameters, const FName Tag = NAME_None);`
- L333 _public prototype_ `FSchemaElement CreateConv2d(const FSchemaConv2dParameters Parameters, const FName Tag = NAME_None);`
- L334 _public prototype_ `FSchemaElement CreateSparse(const FSchemaSparseParameters Parameters, const FName Tag = NAME_None);`
- L335 _public prototype_ `FSchemaElement CreateNamedSparse(const FSchemaNamedSparseParameters Parameters, const FName Tag = NAME_None);`
- L337 _public prototype_ `FSchemaContinuousParameters GetContinuous(const FSchemaElement Element) const;`
- L338 _public prototype_ `FSchemaDiscreteExclusiveParameters GetDiscreteExclusive(const FSchemaElement Element) const;`
- L339 _public prototype_ `FSchemaDiscreteInclusiveParameters GetDiscreteInclusive(const FSchemaElement Element) const;`
- L340 _public prototype_ `FSchemaNamedDiscreteExclusiveParameters GetNamedDiscreteExclusive(const FSchemaElement Element) const;`
- L341 _public prototype_ `FSchemaNamedDiscreteInclusiveParameters GetNamedDiscreteInclusive(const FSchemaElement Element) const;`
- L342 _public prototype_ `FSchemaAndParameters GetAnd(const FSchemaElement Element) const;`
- L343 _public prototype_ `FSchemaOrExclusiveParameters GetOrExclusive(const FSchemaElement Element) const;`
- L344 _public prototype_ `FSchemaOrInclusiveParameters GetOrInclusive(const FSchemaElement Element) const;`
- L345 _public prototype_ `FSchemaArrayParameters GetArray(const FSchemaElement Element) const;`
- L346 _public prototype_ `FSchemaSetParameters GetSet(const FSchemaElement Element) const;`
- L347 _public prototype_ `FSchemaEncodingParameters GetEncoding(const FSchemaElement Element) const;`
- L348 _public prototype_ `FSchemaConv1dParameters GetConv1d(const FSchemaElement Element) const;`
- L349 _public prototype_ `FSchemaConv2dParameters GetConv2d(const FSchemaElement Element) const;`
- L350 _public prototype_ `FSchemaSparseParameters GetSparse(const FSchemaElement Element) const;`
- L351 _public prototype_ `FSchemaNamedSparseParameters GetNamedSparse(const FSchemaElement Element) const;`
- L354 _public prototype_ `bool IsValid(const FSchemaElement Element) const;` — Checks if the given element is valid
- L357 _public prototype_ `EType GetType(const FSchemaElement Element) const;` — Gets the type of the given element
- L360 _public prototype_ `FName GetTag(const FSchemaElement Element) const;` — Gets the tag of the given element
- L363 _public prototype_ `int32 GetObservationVectorSize(const FSchemaElement Element) const;` — Get the observation vector size of the given element
- L366 _public prototype_ `int32 GetEncodedVectorSize(const FSchemaElement Element) const;` — Get the encoded vector size of the given element
- L369 _public prototype_ `int32 GetObservationDistributionVectorSize(const FSchemaElement Element) const;` — Get the observation distribution vector size of the given element
- L372 _public prototype_ `void SetGeneration(const uint32 InGeneration);` — Set the current generation
- L375 _public prototype_ `uint32 GetGeneration() const;` — Get the current generation
- L378 _public prototype_ `bool IsEmpty() const;` — Checks if the given schema is empty of elements.
- L381 _public prototype_ `void Empty();` — Empty all internal buffers of elements. This invalidates all existing elements.
- L384 _public prototype_ `void Reset();` — Reset all internal buffers (without freeing memory). This invalidates all existing elements.
- L387 _public prototype_ `bool Serialize(FArchive& Ar);` — Serializes an observation schema. Returns false if serialization fails.
- L502 _private member_ `uint32 Generation = 0;`
- L505 _private member_ `TArray<EType> Types;` — These have entries for each Schema Element
- L506 _private member_ `TArray<FName> Tags;`
- L507 _private member_ `TArray<int32> ObservationVectorSizes;`
- L508 _private member_ `TArray<int32> EncodedVectorSizes;`
- L509 _private member_ `TArray<int32> ObservationDistributionVectorSizes;`
- L510 _private member_ `TArray<int32> TypeDataIndices;`
- L513 _private member_ `TArray<FContinuousData> ContinuousData;` — These are indexed based on the Type using TypeDataIndices
- L514 _private member_ `TArray<FDiscreteExclusiveData> DiscreteExclusiveData;`
- L515 _private member_ `TArray<FDiscreteInclusiveData> DiscreteInclusiveData;`
- L516 _private member_ `TArray<FNamedDiscreteExclusiveData> NamedDiscreteExclusiveData;`
- L517 _private member_ `TArray<FNamedDiscreteInclusiveData> NamedDiscreteInclusiveData;`
- L518 _private member_ `TArray<FAndData> AndData;`
- L519 _private member_ `TArray<FOrExclusiveData> OrExclusiveData;`
- L520 _private member_ `TArray<FOrInclusiveData> OrInclusiveData;`
- L521 _private member_ `TArray<FArrayData> ArrayData;`
- L522 _private member_ `TArray<FSetData> SetData;`
- L523 _private member_ `TArray<FEncodingData> EncodingData;`
- L524 _private member_ `TArray<FConv1dData> Conv1dData;`
- L525 _private member_ `TArray<FConv2dData> Conv2dData;`
- L526 _private member_ `TArray<FSparseData> SparseData;`
- L527 _private member_ `TArray<FNamedSparseData> NamedSparseData;`
- L530 _private member_ `TArray<FName> SubElementNames;` — This is an array of all the SubElements and their names, referenced by other elements
- L531 _private member_ `TArray<FSchemaElement> SubElementObjects;`
- L534 _private member_ `TArray<float> NormalizationScales;` — Normalization arrays for continuous observations, indexed by NormalizationOffset in FContinuousData
- L535 _private member_ `TArray<float> NormalizationOffsets;`

#### struct `UE::Learning::Observation::FSchema::FContinuousData`  
`struct FContinuousData`  
_L391-396_
- L393 _public member_ `int32 Num = INDEX_NONE;`
- L394 _public member_ `int32 NormalizationIndexOffset = INDEX_NONE;`
- L395 _public member_ `ENormalization NormalizationOption = ENormalization::Manual;`

#### struct `UE::Learning::Observation::FSchema::FDiscreteExclusiveData`  
`struct FDiscreteExclusiveData`  
_L398-401_
- L400 _public member_ `int32 Num = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FDiscreteInclusiveData`  
`struct FDiscreteInclusiveData`  
_L403-406_
- L405 _public member_ `int32 Num = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FNamedDiscreteExclusiveData`  
`struct FNamedDiscreteExclusiveData`  
_L408-412_
- L410 _public member_ `int32 Num = INDEX_NONE;`
- L411 _public member_ `int32 ElementsOffset = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FNamedDiscreteInclusiveData`  
`struct FNamedDiscreteInclusiveData`  
_L414-418_
- L416 _public member_ `int32 Num = INDEX_NONE;`
- L417 _public member_ `int32 ElementsOffset = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FAndData`  
`struct FAndData`  
_L420-424_
- L422 _public member_ `int32 Num = INDEX_NONE;`
- L423 _public member_ `int32 ElementsOffset = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FOrExclusiveData`  
`struct FOrExclusiveData`  
_L426-431_
- L428 _public member_ `int32 Num = INDEX_NONE;`
- L429 _public member_ `int32 ElementsOffset = INDEX_NONE;`
- L430 _public member_ `int32 EncodingSize = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FOrInclusiveData`  
`struct FOrInclusiveData`  
_L433-440_
- L435 _public member_ `int32 Num = INDEX_NONE;`
- L436 _public member_ `int32 ElementsOffset = INDEX_NONE;`
- L437 _public member_ `int32 AttentionEncodingSize = INDEX_NONE;`
- L438 _public member_ `int32 AttentionHeadNum = INDEX_NONE;`
- L439 _public member_ `int32 ValueEncodingSize = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FArrayData`  
`struct FArrayData`  
_L442-446_
- L444 _public member_ `int32 Num = INDEX_NONE;`
- L445 _public member_ `int32 ElementIndex = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FSetData`  
`struct FSetData`  
_L448-455_
- L450 _public member_ `int32 MaxNum = INDEX_NONE;`
- L451 _public member_ `int32 ElementIndex = INDEX_NONE;`
- L452 _public member_ `int32 AttentionEncodingSize = INDEX_NONE;`
- L453 _public member_ `int32 AttentionHeadNum = INDEX_NONE;`
- L454 _public member_ `int32 ValueEncodingSize = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FEncodingData`  
`struct FEncodingData`  
_L457-463_
- L459 _public member_ `int32 ElementIndex = INDEX_NONE;`
- L460 _public member_ `int32 EncodingSize = INDEX_NONE;`
- L461 _public member_ `int32 LayerNum = INDEX_NONE;`
- L462 _public member_ `EEncodingActivationFunction ActivationFunction = EEncodingActivationFunction::ELU;`

#### struct `UE::Learning::Observation::FSchema::FConv1dData`  
`struct FConv1dData`  
_L465-475_
- L467 _public member_ `int32 ElementIndex = INDEX_NONE;`
- L468 _public member_ `int32 InputLength = INDEX_NONE;`
- L469 _public member_ `int32 InChannels = INDEX_NONE;`
- L470 _public member_ `int32 OutChannels = INDEX_NONE;`
- L471 _public member_ `int32 KernelSize = INDEX_NONE;`
- L472 _public member_ `int32 Padding = INDEX_NONE;`
- L473 _public member_ `EPaddingMode PaddingMode = EPaddingMode::Zeros;`
- L474 _public member_ `EEncodingActivationFunction ActivationFunction = EEncodingActivationFunction::ReLU;`

#### struct `UE::Learning::Observation::FSchema::FConv2dData`  
`struct FConv2dData`  
_L477-489_
- L479 _public member_ `int32 ElementIndex = INDEX_NONE;`
- L480 _public member_ `int32 InputHeight = INDEX_NONE;`
- L481 _public member_ `int32 InputWidth = INDEX_NONE;`
- L482 _public member_ `int32 InChannels = INDEX_NONE;`
- L483 _public member_ `int32 OutChannels = INDEX_NONE;`
- L484 _public member_ `int32 KernelSize = INDEX_NONE;`
- L485 _public member_ `int32 Stride = INDEX_NONE;`
- L486 _public member_ `int32 Padding = INDEX_NONE;`
- L487 _public member_ `EPaddingMode PaddingMode = EPaddingMode::Zeros;`
- L488 _public member_ `EEncodingActivationFunction ActivationFunction = EEncodingActivationFunction::ReLU;`

#### struct `UE::Learning::Observation::FSchema::FSparseData`  
`struct FSparseData`  
_L491-494_
- L493 _public member_ `int32 Num = INDEX_NONE;`

#### struct `UE::Learning::Observation::FSchema::FNamedSparseData`  
`struct FNamedSparseData`  
_L496-500_
- L498 _public member_ `int32 Num = INDEX_NONE;`
- L499 _public member_ `int32 ElementsOffset = INDEX_NONE;`

#### struct `UE::Learning::Observation::FObjectElement`  
`struct FObjectElement`  
_L544-544_
- desc: Observation Object Element A single element in the observation object representing part of an observation. Internally this consists of a index used by the object to look up the associated observation data and a generation id which can be used to check when this index is no longer valid.
- L544 _public member_ `struct FObjectElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Observation Object Element A single element in the observation object representing part of an observation. Internally this consists of a index used by the object to look up the associated observation data and a generation id which can be used to check when this index is no longer valid.
- L544 _public member_ `struct FObjectElement { int32 Index = INDEX_NONE; uint32 Generation = INDEX_NONE; };` — Observation Object Element A single element in the observation object representing part of an observation. Internally this consists of a index used by the object to look up the associated observation data and a generation id which can be used to check when this index is no longer valid.

#### struct `UE::Learning::Observation::FObjectContinuousParameters`  
`struct FObjectContinuousParameters`  
_L546-550_
- L549 _public member_ `TArrayView<const float> Values;` — Continuous observation values

#### struct `UE::Learning::Observation::FObjectDiscreteExclusiveParameters`  
`struct FObjectDiscreteExclusiveParameters`  
_L552-556_
- L555 _public member_ `int32 DiscreteIndex;` — Index of the chosen observation.

#### struct `UE::Learning::Observation::FObjectDiscreteInclusiveParameters`  
`struct FObjectDiscreteInclusiveParameters`  
_L558-562_
- L561 _public member_ `TArrayView<const int32> DiscreteIndices;` — Indices of the chosen observations.

#### struct `UE::Learning::Observation::FObjectNamedDiscreteExclusiveParameters`  
`struct FObjectNamedDiscreteExclusiveParameters`  
_L564-568_
- L567 _public member_ `FName ElementName;` — Name of the chosen observation.

#### struct `UE::Learning::Observation::FObjectNamedDiscreteInclusiveParameters`  
`struct FObjectNamedDiscreteInclusiveParameters`  
_L570-574_
- L573 _public member_ `TArrayView<const FName> ElementNames;` — Names of the chosen observations.

#### struct `UE::Learning::Observation::FObjectAndParameters`  
`struct FObjectAndParameters`  
_L576-583_
- L579 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sub-observations.
- L582 _public member_ `TArrayView<const FObjectElement> Elements;` — The associated sub-element.

#### struct `UE::Learning::Observation::FObjectOrExclusiveParameters`  
`struct FObjectOrExclusiveParameters`  
_L585-592_
- L588 _public member_ `FName ElementName;` — Name of the chosen sub-observation.
- L591 _public member_ `FObjectElement Element;` — The associated chosen sub-element.

#### struct `UE::Learning::Observation::FObjectOrInclusiveParameters`  
`struct FObjectOrInclusiveParameters`  
_L594-601_
- L597 _public member_ `TArrayView<const FName> ElementNames;` — Names of the chosen sub-observations.
- L600 _public member_ `TArrayView<const FObjectElement> Elements;` — The associated chosen sub-elements.

#### struct `UE::Learning::Observation::FObjectArrayParameters`  
`struct FObjectArrayParameters`  
_L603-607_
- L606 _public member_ `TArrayView<const FObjectElement> Elements;` — Array of sub-elements.

#### struct `UE::Learning::Observation::FObjectSetParameters`  
`struct FObjectSetParameters`  
_L609-613_
- L612 _public member_ `TArrayView<const FObjectElement> Elements;` — Set of sub-elements.

#### struct `UE::Learning::Observation::FObjectEncodingParameters`  
`struct FObjectEncodingParameters`  
_L615-619_
- L618 _public member_ `FObjectElement Element;` — Encoded sub-element.

#### struct `UE::Learning::Observation::FObjectConv1dParameters`  
`struct FObjectConv1dParameters`  
_L621-625_
- L624 _public member_ `FObjectElement Element;` — Encoded sub-element.

#### struct `UE::Learning::Observation::FObjectConv2dParameters`  
`struct FObjectConv2dParameters`  
_L627-631_
- L630 _public member_ `FObjectElement Element;` — Encoded sub-element.

#### struct `UE::Learning::Observation::FObjectSparseParameters`  
`struct FObjectSparseParameters`  
_L633-640_
- L636 _public member_ `TArrayView<const int32> DiscreteIndices;` — Indices of the sparse observations.
- L639 _public member_ `TArrayView<const float> Values;` — Sparse observation values

#### struct `UE::Learning::Observation::FObjectNamedSparseParameters`  
`struct FObjectNamedSparseParameters`  
_L642-649_
- L645 _public member_ `TArrayView<const FName> ElementNames;` — Names of the sparse observations.
- L648 _public member_ `TArrayView<const float> Values;` — Sparse observation values

#### struct `UE::Learning::Observation::FObject`  
`struct FObject`  
_L658-737_
- desc: Observation Object This object allows you to construct or get data from an instance of an observation you might give as input to a policy. Internally this object contains a pool of individual elements. This allows them to be constructed performantly and in a cache efficient way. This object is therefore required to access any data about the individual observation elements that are created.
- L660 _public prototype_ `FObjectElement CreateNull(const FName Tag = NAME_None);`
- L661 _public prototype_ `FObjectElement CreateContinuous(const FObjectContinuousParameters Parameters, const FName Tag = NAME_None);`
- L662 _public prototype_ `FObjectElement CreateDiscreteExclusive(const FObjectDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L663 _public prototype_ `FObjectElement CreateDiscreteInclusive(const FObjectDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L664 _public prototype_ `FObjectElement CreateNamedDiscreteExclusive(const FObjectNamedDiscreteExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L665 _public prototype_ `FObjectElement CreateNamedDiscreteInclusive(const FObjectNamedDiscreteInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L666 _public prototype_ `FObjectElement CreateAnd(const FObjectAndParameters Parameters, const FName Tag = NAME_None);`
- L667 _public prototype_ `FObjectElement CreateOrExclusive(const FObjectOrExclusiveParameters Parameters, const FName Tag = NAME_None);`
- L668 _public prototype_ `FObjectElement CreateOrInclusive(const FObjectOrInclusiveParameters Parameters, const FName Tag = NAME_None);`
- L669 _public prototype_ `FObjectElement CreateArray(const FObjectArrayParameters Parametes, const FName Tag = NAME_None);`
- L670 _public prototype_ `FObjectElement CreateSet(const FObjectSetParameters Parameters, const FName Tag = NAME_None);`
- L671 _public prototype_ `FObjectElement CreateEncoding(const FObjectEncodingParameters Parameters, const FName Tag = NAME_None);`
- L672 _public prototype_ `FObjectElement CreateConv1d(const FObjectConv1dParameters Parameters, const FName Tag = NAME_None);`
- L673 _public prototype_ `FObjectElement CreateConv2d(const FObjectConv2dParameters Parameters, const FName Tag = NAME_None);`
- L674 _public prototype_ `FObjectElement CreateSparse(const FObjectSparseParameters Parameters, const FName Tag = NAME_None);`
- L675 _public prototype_ `FObjectElement CreateNamedSparse(const FObjectNamedSparseParameters Parameters, const FName Tag = NAME_None);`
- L677 _public prototype_ `FObjectContinuousParameters GetContinuous(const FObjectElement Element) const;`
- L678 _public prototype_ `FObjectDiscreteExclusiveParameters GetDiscreteExclusive(const FObjectElement Element) const;`
- L679 _public prototype_ `FObjectDiscreteInclusiveParameters GetDiscreteInclusive(const FObjectElement Element) const;`
- L680 _public prototype_ `FObjectNamedDiscreteExclusiveParameters GetNamedDiscreteExclusive(const FObjectElement Element) const;`
- L681 _public prototype_ `FObjectNamedDiscreteInclusiveParameters GetNamedDiscreteInclusive(const FObjectElement Element) const;`
- L682 _public prototype_ `FObjectAndParameters GetAnd(const FObjectElement Element) const;`
- L683 _public prototype_ `FObjectOrExclusiveParameters GetOrExclusive(const FObjectElement Element) const;`
- L684 _public prototype_ `FObjectOrInclusiveParameters GetOrInclusive(const FObjectElement Element) const;`
- L685 _public prototype_ `FObjectArrayParameters GetArray(const FObjectElement Element) const;`
- L686 _public prototype_ `FObjectSetParameters GetSet(const FObjectElement Element) const;`
- L687 _public prototype_ `FObjectEncodingParameters GetEncoding(const FObjectElement Element) const;`
- L688 _public prototype_ `FObjectConv1dParameters GetConv1d(const FObjectElement Element) const;`
- L689 _public prototype_ `FObjectConv2dParameters GetConv2d(const FObjectElement Element) const;`
- L690 _public prototype_ `FObjectSparseParameters GetSparse(const FObjectElement Element) const;`
- L691 _public prototype_ `FObjectNamedSparseParameters GetNamedSparse(const FObjectElement Element) const;`
- L694 _public prototype_ `bool IsValid(const FObjectElement Element) const;` — Checks if the given element is valid
- L697 _public prototype_ `EType GetType(const FObjectElement Element) const;` — Gets the type of the given element
- L700 _public prototype_ `FName GetTag(const FObjectElement Element) const;` — Gets the tag of the given element
- L703 _public prototype_ `void SetGeneration(const uint32 InGeneration);` — Set the current generation
- L706 _public prototype_ `uint32 GetGeneration() const;` — Get the current generation
- L709 _public prototype_ `bool IsEmpty() const;` — Checks if the given object is empty of elements.
- L712 _public prototype_ `void Empty();` — Empty all internal buffers of elements. This invalidates all existing elements.
- L715 _public prototype_ `void Reset();` — Reset all internal buffers (without freeing memory). This invalidates all existing elements.
- L718 _public prototype_ `bool Serialize(FArchive& Ar);` — Serializes an observation object. Returns false if serialization fails.
- L722 _private member_ `uint32 Generation = 0;`
- L724 _private member_ `TArray<EType> Types;`
- L725 _private member_ `TArray<FName> Tags;`
- L726 _private member_ `TArray<int32> ContinuousDataOffsets;`
- L727 _private member_ `TArray<int32> ContinuousDataNums;`
- L728 _private member_ `TArray<int32> DiscreteDataOffsets;`
- L729 _private member_ `TArray<int32> DiscreteDataNums;`
- L730 _private member_ `TArray<int32> SubElementDataOffsets;`
- L731 _private member_ `TArray<int32> SubElementDataNums;`
- L733 _private member_ `TArray<float> ContinuousValues;`
- L734 _private member_ `TArray<int32> DiscreteValues;`
- L735 _private member_ `TArray<FName> SubElementNames;`
- L736 _private member_ `TArray<FObjectElement> SubElementObjects;`

#### enum `UE::Learning::Observation::EWeightInitialization`  
`enum class EWeightInitialization : uint8`  
_L769-773_
- desc: Network weight initialization type
- L771 _public enumerator_ `KaimingGaussian = 0`
- L772 _public enumerator_ `KaimingUniform = 1`

#### struct `UE::Learning::Observation::FNetworkSettings`  
`struct FNetworkSettings`  
_L778-785_
- desc: Settings for building a network from a schema.
- L781 _public member_ `bool bUseCompressedLinearLayers = false;` — If to use compressed linear layers. This reduces the memory usage by half at the cost of some small impact on quality and evaluation speed.
- L784 _public member_ `EWeightInitialization WeightInitialization = EWeightInitialization::KaimingGaussian;` — Which weight initialization to use.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNING_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNE` (scope `UE`)
- L11 _namespace_ `namespace RuntimeBasic` (scope `UE::NNE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Learning` (scope `UE`)
- L17 _namespace_ `namespace Observation` (scope `UE::Learning`)
- L83 _function_ `static inline FString GetNormalizationOptionAsString(const ENormalization NormalizationOption)` (scope `UE::Learning::Observation`)
- L748 _prototype_ `int32 GetSchemaObjectsCompatibilityHash( const FSchema& Schema, const FSchemaElement SchemaElement, const int32 Salt = 0x62625165);` (scope `UE::Learning::Observation`) — Gets a hash value representing object compatibility between schemas i.e. if objects from one schema can be used by objects expecting another schema. This is not a cryptographic hash, and so `AreSchemaObjectsCompatible` should still be used as the ultimate source of truth. This function returns an int32 so that it can be used in blueprints. @param Schema					Observation Schema @param SchemaElement				Observation Schema Element @param Salt						Hash salt
- L762 _prototype_ `bool AreSchemaObjectsCompatible( const FSchema& SchemaA, const FSchemaElement SchemaElementA, const FSchema& SchemaB, const FSchemaElement SchemaElementB);` (scope `UE::Learning::Observation`) — Test if two schemas are compatible i.e. if objects from one schema can be used by objects expecting another schema. @param SchemaA					First Schema @param SchemaElementA			First Schema Element @param SchemaB					Second Schema @param SchemaElementB			Second Schema Element @returns							true when the schemas are compatible
- L797 _prototype_ `void MakeEncoderNetworkModelBuilderElementFromSchema( NNE::RuntimeBasic::FModelBuilderElement& OutElement, NNE::RuntimeBasic::FModelBuilder& Builder, const FSchema& Schema, const FSchemaElement SchemaElement, const FNetworkSettings& NetworkSettings = FNetworkSettings());` (scope `UE::Learning::Observation`) — Make a NNE::RuntimeBasic::FModelBuilderElement for the given Schema. This can be used if you want to plug the Encoder generated by this schema as a part of a larger model you are making with a NNE::RuntimeBasic::FModelBuilder. @param OutElement				Output Builder Element @param Builder					Model Builder @param Schema					Observation Schema @param SchemaElement				Observation Schema Element @param NetworkSettings			Network Generation Settings
- L816 _prototype_ `void GenerateEncoderNetworkFileDataFromSchema( TArray<uint8>& OutFileData, uint32& OutInputSize, uint32& OutOutputSize, const FSchema& Schema, const FSchemaElement SchemaElement, const FNetworkSettings& NetworkSettings = FNetworkSettings(), const uint32 Seed = 0x08ab1c49);` (scope `UE::Learning::Observation`) — Generate FileData for a Neural Network that can act as a Encoder for the given schema. This network will take as input a vector of size ObservationVectorSize and produce a vector of size EncodedVectorSize. @param OutFileData				Output File Data to write to @param OutInputSize				Size of the vector this network takes as input @param OutOutputSize				Size of the vector this network takes as output @param Schema					Observation Schema @param SchemaElement				Observation Schema Element @param NetworkSettings			Network Generation Settings @param Seed						The random seed used in initializing the network weights
- L834 _prototype_ `void SetVectorFromObject( TLearningArrayView<1, float> OutObservationVector, const FSchema& Schema, const FSchemaElement SchemaElement, const FObject& Object, const FObjectElement ObjectElement);` (scope `UE::Learning::Observation`) — Convert an observation object into an observation vector. @param OutObservationVector		Output observation vector @param Schema					Observation Schema @param SchemaElement				Observation Schema Element @param Object					Observation Object @param ObjectElement				Observation Object Element
- L850 _prototype_ `void GetObjectFromVector( FObject& OutObject, FObjectElement& OutObjectElement, const FSchema& Schema, const FSchemaElement SchemaElement, const TLearningArrayView<1, const float> ObservationVector);` (scope `UE::Learning::Observation`) — Convert an observation vector into an observation object @param OutObject					Output Observation Object @param OutObjectElement			Output Observation Object Element @param Schema					Observation Schema @param SchemaElement				Observation Schema Element @param ObservationVector			Input Observation vector
- L867 _prototype_ `void GetContinuousObservationVectorMask( TLearningArrayView<1, bool> OutObservationVectorMask, const TLearningArrayView<1, const float> InObservationVector, const FSchema& Schema, const FSchemaElement SchemaElement);` (scope `UE::Learning::Observation`) — Outputs a vector mask which has 1s for entries in the observation vector which correspond to continuous observation values and 0s elsewhere. This can be useful if you want to apply some kind of numerical modifications to observation vectors such as adding noise or clamping, without breaking the parts of the vector which encode the structure. @param OutObservationVectorMask	Observation vector mask @param InObservationVector		Input observation vector @param Schema					Observation Schema @param SchemaElement				Observation Schema Element
- L879 _prototype_ `void InitObservationDistributionMinMax( TLearningArrayView<1, float> OutObservationDistributionMin, TLearningArrayView<1, float> OutObservationDistributionMax);` (scope `UE::Learning::Observation`) — Initializes mins and maxs for observation distribution vectors. Should be called before any calls to FitObservationDistributionMinMax @param OutObservationDistributionMin		Minimum values for observations @param OutObservationDistributionMax		Maximum values for observations
- L893 _prototype_ `void FitObservationDistributionMinMax( TLearningArrayView<1, float> InOutObservationDistributionMin, TLearningArrayView<1, float> InOutObservationDistributionMax, const TLearningArrayView<1, const float> InObservationVector, const FSchema& Schema, const FSchemaElement SchemaElement);` (scope `UE::Learning::Observation`) — Fits the mins and the maxs of each continuous observation in the observation vector. Typically you will want to call this function in a loop over multiple observation vectors to refine the fitted mins and maxs since this updates them in place. @param InOutObservationDistributionMin		Minimum values for observations @param InOutObservationDistributionMax		Maximum values for observations @param InObservationVector					Observation vector to fit the mins and maxs from @param Schema								Observation Schema @param SchemaElement							Observation Schema Element
- L909 _prototype_ `void ClampToObservationDistributionMinMax( TLearningArrayView<1, float> InOutObservationVector, const TLearningArrayView<1, const float> ObservationDistributionMin, const TLearningArrayView<1, const float> ObservationDistributionMax, const FSchema& Schema, const FSchemaElement SchemaElement);` (scope `UE::Learning::Observation`) — Clamps an observation vector using mins and maxs given by two observation distribution vectors. @param InOutObservationVector				Observation vector to clamp @param ObservationDistributionMin			Minimum values for observations @param ObservationDistributionMax			Maximum values for observations @param Schema								Observation Schema @param SchemaElement							Observation Schema Element
- L918 _prototype_ `FArchive& operator<<(FArchive& Ar, UE::Learning::Observation::FSchemaElement& SchemaElement);`
- L919 _prototype_ `FArchive& operator<<(FArchive& Ar, UE::Learning::Observation::FObjectElement& ObjectElement);`
- L920 _prototype_ `bool operator==(const UE::Learning::Observation::FSchemaElement& Lhs, const UE::Learning::Observation::FSchemaElement& Rhs);`
- L921 _prototype_ `bool operator==(const UE::Learning::Observation::FObjectElement& Lhs, const UE::Learning::Observation::FObjectElement& Rhs);`
- L922 _prototype_ `uint32 GetTypeHash(const UE::Learning::Observation::FSchemaElement& SchemaElement);`
- L923 _prototype_ `uint32 GetTypeHash(const UE::Learning::Observation::FObjectElement& ObjectElement);`

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningOptimizationPlanner.h` (Public)


#### struct `UE::Learning::FOptimizationPlannerBuffer`  
`struct FOptimizationPlannerBuffer`  
_L18-27_
- desc: Basic buffer containing some additional data used during optimization planning
- L20 _public prototype_ `void Resize( const int32 SampleNum, const int32 StepNum, const int32 ActionVectorDimensionNum);`
- L25 _public member_ `TLearningArray<3, float> Samples;`
- L26 _public member_ `TLearningArray<1, float> Losses;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LEARNING_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Learning` (scope `UE`)
- L29 _namespace_ `namespace OptimizationPlanner` (scope `UE::Learning`)
- L42 _prototype_ `void RunPlan( TLearningArrayView<2, float> ActionVectorBuffer, const TFunctionRef<void(const FIndexSet Instances)> ResetFunction, const TFunctionRef<void(const FIndexSet Instances)> ActionFunction, const TFunctionRef<void(const FIndexSet Instances)> UpdateFunction, const TLearningArrayView<3, const float> ActionVectors, const FIndexSet Instances);` (scope `UE::Learning::OptimizationPlanner`) — Runs a sequence of action vectors for a set instances @param ActionVectorBuffer				Buffer to write action vectors into @param ResetFunction					Function to run for resetting the environment @param ActionFunction					Function to run for evaluating actions @param UpdateFunction					Function to run for updating the environment @param ActionVectors					Action Vectors of shape (StepNum, InstanceNum, ActionVectorDimNum) @param Instances						Set of instances to run action vectors for
- L69 _prototype_ `void Plan( TLearningArrayView<2, float> InOutActionVectors, FOptimizationPlannerBuffer& OptimizationPlannerBuffer, IOptimizer& Optimizer, TLearningArrayView<2, float> ActionVectorBuffer, TLearningArrayView<1, float> RewardBuffer, const int32 IterationNum, const TFunctionRef<void(const FIndexSet Instances)> ResetFunction, const TFunctionRef<void(const FIndexSet Instances)> ActionFunction, const TFunctionRef<void(const FIndexSet Instances)> UpdateFunction, const TFunctionRef<void(const FIndexSet Instances)> RewardFunction, const FIndexSet SampleInstances, const ELogSetting LogSettings = ELogSetting::Normal, FProgress* Progress = nullptr, FRWLock* ActionVectorsLock = nullptr, TAtomic<bool>* bActionVectorsUpdatedFlag = nullptr);` (scope `UE::Learning::OptimizationPlanner`) — Run the optimization based planner on the provided action vectors to maximize the reward @param InOutActionVectors				Action vectors to adjust of shape (StepNum, ActionVectorDimNum) @param OptimizationPlannerBuffer		Buffer for the optimization planner @param Optimizer						Optimizer to use @param ActionVectorBuffer				Buffer to read/write action vectors into @param RewardBuffer					Buffer to read/write rewards into @param IterationNum					Number of iterations to run the planner for @param ResetFunction					Function to run for resetting the environment @param ActionFunction					Function to run for evaluating actions @param UpdateFunction					Function to run for updating the environment @param RewardFunction					Function to run for evaluating rewards @param SampleInstances				Instances to use for sampling during the optimization @param LogSettings					Log settings to use @param Progress						Optional progress to record progress in @param ActionVectorsLock				Optional lock to use when updating InOutActionVectors @param bActionVectorsUpdatedFlag		Optional signal to set when updating InOutActionVectors
- L113 _prototype_ `void PlanWindowed( TLearningArrayView<2, float> InOutActionVectors, FOptimizationPlannerBuffer& OptimizationPlannerBuffer, IOptimizer& Optimizer, TLearningArrayView<2, float> ActionVectorBuffer, TLearningArrayView<1, float> RewardBuffer, const int32 InitialIterationsNum, const int32 FinalIterationsNum, const int32 WindowIterationsNum, const int32 WindowStepNum, const TFunctionRef<void(const FIndexSet Instances)> ResetFunction, const TFunctionRef<void(const FIndexSet Instances, const int32 Instance)> ResetFromInstanceFunction, const TFunctionRef<void(const FIndexSet Instances)> ActionFunction, const TFunctionRef<void(const FIndexSet Instances)> UpdateFunction, const TFunctionRef<void(const FIndexSet Instances)> RewardFunction, const int32 PlanInstance, const FIndexSet SampleInstances, const ELogSetting LogSettings = ELogSetting::Normal, FProgress* Progress = nullptr, FRWLock* ActionVectorsLock = nullptr, TAtomic<bool>* bActionVectorsUpdatedFlag = nullptr);` (scope `UE::Learning::OptimizationPlanner`) — Run the optimization based planner windowed on the provided action vectors to maximize the reward. In windowed mode the optimization planner will only optimize a fixed window of steps over the action vectors at a time. This gives the optimizer an easier job, but limits how for the system can plan ahead. @param InOutActionVectors				Action vectors to adjust of shape (StepNum, ActionVectorDimNum) @param OptimizationPlannerBuffer		Buffer for the optimization planner @param Optimizer						Optimizer to use @param ActionVectorBuffer				Buffer to read/write action vectors into @param RewardBuffer					Buffer to read/write rewards into @param InitialIterationsNum			Number of iterations to run the planner for on the initial window @param FinalIterationsNum				Number of iterations to run the planner for on the final window @param WindowIterationsNum			Number of iterations to run the planner for on the intermediate windows @param WindowStepNum					Number of steps to consider in the window @param ResetFunction					Function to run for resetting the environment @param ResetFromInstanceFunction		Function to run to reset the planning instances from the state of single instance @param ActionFunction					Function to run for evaluating actions @param UpdateFunction					Function to run for updating the environment @param RewardFunction					Function to run for evaluating rewards @param PlanInstance					The instance used to execute the plan. Should not be included in the SampleInstances. @param Sam

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningOptimizer.h` (Public)


#### struct `UE::Learning::IOptimizer`  
`struct IOptimizer`  
_L13-46_
- desc: Interface for an Optimizer
- L15 _public prototype_ `virtual ~IOptimizer() = default;`
- L23 _public prototype_ `virtual void Resize(const int32 SampleNum, const int32 DimensionsNum) = 0;` — Resize the Optimizer @param SampleNum			Number of samples to allocate space for @param DimensionsNum		Number of dimensions to allocate space for
- L31 _public prototype_ `virtual void Reset( TLearningArrayView<2, float> OutSamples, const TLearningArrayView<1, const float> InitialGuess) = 0;` — Reset the Optimizer @param OutSamples			Output parameters for which to compute the loss function of shape (SamplesNum, DimensionsNum) @param InitialGuess		Initial guess at the best solution of shape (DimensionsNum). Can be set to zero if no initial guess is known.
- L42 _public prototype_ `virtual void Update( TLearningArrayView<2, float> InOutSamples, const TLearningArrayView<1, const float> Losses, const ELogSetting LogSettings = ELogSetting::Normal) = 0;` — Update the Optimizer @param InOutSamples		Samples to adjust the values of in-place of shape (SamplesNum, DimensionsNum) @param Losses				Losses associated with those samples of shape (SamplesNum) @param LogSettings		Log settings

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningPCA.h` (Public)


#### struct `UE::Learning::FPCASettings`  
`struct FPCASettings`  
_L21-35_
- desc: PCA settings. The resulting number of dimensions will be based on whatever is lower between `MaximumDimensions`, and however many dimensions preserve the given `MaximumVarianceRatio`. If the PCA computation is failing ensure `bStableComputation` is set to true as the non-stable version fails more often than I would expect.
- L25 _public member_ `int32 Subsample = 1;` — Rate at which to subsample the data when computing the PCA encoding. Higher values will make the PCA computation faster but less accurate.
- L28 _public member_ `int32 MaximumDimensions = 128;` — Maximum number of dimensions to keep
- L31 _public member_ `float MaximumVarianceRatio = 0.99f;` — Maximum variance ratio to preserve
- L34 _public member_ `bool bStableComputation = true;` — Use a slower but stable version of the computation

#### struct `UE::Learning::FPCAResult`  
`struct FPCAResult`  
_L40-50_
- desc: Details of the result of the PCA fitting.
- L43 _public member_ `bool bSuccess = false;` — Was the PCA transform fit successfully
- L46 _public member_ `int32 DimensionNum = 0;` — How many dimensions were kept by the PCA transform
- L49 _public member_ `float VarianceRatioPreserved = 0.0f;` — Number between 0 and 1 saying how much of the variance is preserved

#### struct `UE::Learning::FPCAEncoder`  
`struct FPCAEncoder`  
_L55-112_
- desc: Represents a PCA transformation which can be used to encode data
- L57 _public member_ `TLearningArray<2, float> Matrix;`
- L59 _public prototype_ `void Empty();`
- L60 _public prototype_ `bool IsEmpty() const;`
- L61 _public prototype_ `bool Serialize(FArchive& Ar);`
- L63 _public prototype_ `int32 DimensionNum() const;`
- L64 _public prototype_ `int32 FeatureNum() const;`
- L75 _public prototype_ `FPCAResult Fit( const TLearningArrayView<2, const float> Data, const FPCASettings& Settings, const ELogSetting LogSettings = ELogSetting::Normal, FProgress* Progress = nullptr);` — Fits a PCA transform to some data @param Data				Data to fit the PCA transformation to of shape (SampleNum, FeatureNum). Assumes data is already centered and normalized. @param Settings			Fitting settings @param LogSettings		Logging settings @param Progress			Optional progress object to report progress @returns					Result of PCA fitting process. Used to check for success.
- L88 _public prototype_ `void Transform( TLearningArrayView<2, float> OutData, const TLearningArrayView<2, const float> Data, FProgress* Progress = nullptr) const;` — Transform multiple vectors using the PCA transformation @param OutData			Output transformed data of shape (SampleNum, DimensionNum) @param Data				Data to transform of shape (SampleNum, FeatureNum) @param Progress			Optional progress object to report progress
- L99 _public prototype_ `void Transform( TLearningArrayView<1, float> OutData, const TLearningArrayView<1, const float> Data) const;` — Transform a single vector using the PCA transformation @param OutData			Output transformed data of shape (DimensionNum) @param Data				Data to transform of shape (FeatureNum)
- L109 _public prototype_ `void InverseTransform( TLearningArrayView<1, float> OutData, const TLearningArrayView<1, const float> Data) const;` — Inverse Transform a single vector using the PCA transformation @param OutData			Output transformed data of shape (FeatureNum) @param Data				Data to transform of shape (DimensionNum)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LEARNING_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningPSOOptimizer.h` (Public)


#### struct `UE::Learning::FPSOOptimizerSettings`  
`struct FPSOOptimizerSettings`  
_L14-24_
- desc: Settings for the PSO Optimizer. Defaults from https://www.jstage.jst.go.jp/article/imt/3/1/3_1_103/_pdf/-char/ja
- L17 _public member_ `float LocalGain = 1.49455f;` — Amount to pull particles toward their local best
- L20 _public member_ `float GlobalGain = 1.49455f;` — Amount to pull particles toward the global best
- L23 _public member_ `float Momentum = 0.729f;` — How much of the particle velocity to preserve between steps

#### struct `UE::Learning::FPSOOptimizer`  
`struct FPSOOptimizer : public IOptimizer`  
_L31-60_
- inherits: `IOptimizer`
- desc: PSO Optimizer Gradient free optimizer based on Particle Swarm Optimization
- L33 _public prototype_ `FPSOOptimizer(const uint32 Seed, const FPSOOptimizerSettings& InSettings = FPSOOptimizerSettings());`
- L35 _public prototype_ `virtual void Resize(const int32 SampleNum, const int32 DimensionsNum) override final;`
- L37 _public prototype_ `virtual void Reset( TLearningArrayView<2, float> OutSamples, const TLearningArrayView<1, const float> InitialGuess) override final;`
- L41 _public prototype_ `virtual void Update( TLearningArrayView<2, float> InOutSamples, const TLearningArrayView<1, const float> Losses, const ELogSetting LogSettings = ELogSetting::Normal) override final;`
- L48 _private member_ `uint32 Seed = 0;`
- L49 _private member_ `FPSOOptimizerSettings Settings;`
- L51 _private member_ `int32 Iterations = 0;`
- L52 _private member_ `TLearningArray<2, float> LocalBestPositions;`
- L53 _private member_ `TLearningArray<1, float> LocalBestLoss;`
- L54 _private member_ `TLearningArray<1, float> GlobalBestPosition;`
- L55 _private member_ `float GlobalBestLoss = 0.0f;`
- L56 _private member_ `TLearningArray<2, float> Velocities;`
- L58 _private member_ `TLearningArray<2, float> LocalUniformSamples;`
- L59 _private member_ `TLearningArray<2, float> GlobalUniformSamples;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEARNING_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningPolicy.h` (Public)


#### struct `UE::Learning::FNeuralNetworkPolicy`  
`struct FNeuralNetworkPolicy`  
_L17-68_
- desc: Neural-network based policy object. Stores various settings and intermediate storage required to evaluate the given network for the provided number of instances.
- L29 _public prototype_ `FNeuralNetworkPolicy( const int32 InMaxInstanceNum, const int32 InObservationEncodedNum, const int32 InActionEncodedNum, const int32 InMemoryStateNum, const TSharedPtr<FNeuralNetwork>& InNeuralNetwork, const FNeuralNetworkInferenceSettings& InInferenceSettings = FNeuralNetworkInferenceSettings());` — Create a new Policy Object which takes the encoded observation state, and the memory state, and outputs the encoded action state. @param InMaxInstanceNum				Maximum number of instances @param InObservationEncodedNum		Size of the encoded observation vector @param InActionEncodedNum			Size of the encoded action vector @param InMemoryStateNum				Size of the memory state @param InNeuralNetwork				Neural network object @param InInferenceSettings			Inference settings
- L46 _public prototype_ `void Evaluate( TLearningArrayView<2, float> OutputActionVectorsEncoded, TLearningArrayView<2, float> OutputMemoryState, const TLearningArrayView<2, const float> InputObservationVectorsEncoded, const TLearningArrayView<2, const float> InputMemoryState, const FIndexSet Instances);` — Evaluate the Policy @param OutputActionVectorsEncoded		Output encoded action vectors of shape (MaxInstanceNum, ActionEncodedNum) @param OutputMemoryState					Output updated memory state of shape (MaxInstanceNum, MemoryStateNum) @param InputObservationVectorsEncoded	Input encoded observation vectors of shape (MaxInstanceNum, ObservationEncodedNum) @param InputMemoryState					Input memory state of shape (MaxInstanceNum, MemoryStateNum) @param Instances							Set of instances to evaluate
- L54 _public prototype_ `void UpdateNeuralNetwork(const TSharedPtr<FNeuralNetwork>& NewNeuralNetwork);` — Sets the NeuralNetwork and re-creates the NeuralNetworkInference object
- L57 _public prototype_ `const TSharedPtr<FNeuralNetwork>& GetNeuralNetwork() const;` — Gets the NeuralNetwork associated with this Policy
- L61 _private member_ `int32 ObservationEncodedNum = 0;`
- L62 _private member_ `int32 ActionEncodedNum = 0;`
- L63 _private member_ `int32 MemoryStateNum = 0;`
- L64 _private member_ `TSharedPtr<FNeuralNetworkFunction> NeuralNetworkFunction;`
- L66 _private member_ `TLearningArray<2, float> Input;`
- L67 _private member_ `TLearningArray<2, float> Output;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNING_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningProgress.h` (Public)


#### struct `UE::Learning::FProgress`  
`struct FProgress`  
_L15-31_
- desc: Simple thread-safe structure to record progress of some long-running computation.
- L17 _public prototype_ `int32 GetProgress() const;`
- L18 _public prototype_ `void SetProgress(const int32 InProgress);`
- L20 _public prototype_ `void GetMessage(FText& OutMessage);`
- L21 _public prototype_ `void SetMessage(const FText& InMessage);`
- L23 _public prototype_ `void Decrement();`
- L24 _public prototype_ `void Decrement(const int32 Num);`
- L25 _public prototype_ `void Done();`
- L28 _private member_ `FRWLock Lock;`
- L29 _private member_ `FText Message;`
- L30 _private member_ `TAtomic<int32> Progress = 0;`

#### struct `UE::Learning::FScopeNullableReadLock`  
`struct FScopeNullableReadLock`  
_L36-49_
- desc: Scoped read lock, which can optionally be null
- L40 _public prototype_ `UE_NODISCARD_CTOR FScopeNullableReadLock(FRWLock* InLock);`
- L41 _public prototype_ `~FScopeNullableReadLock();`
- L43 _public prototype_ `FScopeNullableReadLock() = delete;`
- L44 _public prototype_ `FScopeNullableReadLock(const FScopeNullableReadLock& InScopeLock) = delete;`
- L45 _public prototype_ `FScopeNullableReadLock& operator=(FScopeNullableReadLock& InScopeLock) = delete;`
- L48 _private member_ `FRWLock* Lock = nullptr;`

#### struct `UE::Learning::FScopeNullableWriteLock`  
`struct FScopeNullableWriteLock`  
_L54-67_
- desc: Scoped write lock, which can optionally be null
- L58 _public prototype_ `UE_NODISCARD_CTOR FScopeNullableWriteLock(FRWLock* InLock);`
- L59 _public prototype_ `~FScopeNullableWriteLock();`
- L61 _public prototype_ `FScopeNullableWriteLock() = delete;`
- L62 _public prototype_ `FScopeNullableWriteLock(const FScopeNullableWriteLock& InScopeLock) = delete;`
- L63 _public prototype_ `FScopeNullableWriteLock& operator=(FScopeNullableWriteLock& InScopeLock) = delete;`
- L66 _private member_ `FRWLock* Lock = nullptr;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LEARNING_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/LearningRandom.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LEARNING_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Learning` (scope `UE`)
- L58 _namespace_ `namespace UE`
- L58 _namespace_ `namespace Learning` (scope `UE`)
- L58 _namespace_ `namespace Random` (scope `UE::Learning`)
- L66 _prototype_ `uint32 Int(const uint32 State);` (scope `UE::Learning::Random`)
- L68 _prototype_ `float Float(const uint32 State);` (scope `UE::Learning::Random`)
- L70 _prototype_ `int32 IntInRange(const uint32 State, const int32 Min, const int32 Max);` (scope `UE::Learning::Random`)
- L72 _prototype_ `float Uniform( const uint32 State, const float Min = 0.0f, const float Max = 1.0f);` (scope `UE::Learning::Random`)
- L77 _prototype_ `float Gaussian( const uint32 State, const float Mean = 0.0f, const float Std = 1.0f);` (scope `UE::Learning::Random`)
- L82 _prototype_ `FVector VectorGaussian( const uint32 State, const FVector Mean = FVector::ZeroVector, const FVector Std = FVector::OneVector);` (scope `UE::Learning::Random`)
- L87 _prototype_ `float ClippedGaussian( const uint32 State, const float Mean = 0.0f, const float Std = 1.0f, const float Clip = 10.0f);` (scope `UE::Learning::Random`)
- L93 _prototype_ `FVector PlanarUniform( const uint32 State, const float Min = 0.0f, const float Max = 1.0f, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L100 _prototype_ `FVector PlanarGaussian( const uint32 State, const float Mean = 0.0f, const float Std = 1.0f, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L107 _prototype_ `FVector PlanarClippedGaussian( const uint32 State, const float Mean = 0.0f, const float Std = 1.0f, const float Clip = 10.0f, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L115 _prototype_ `FVector PlanarDirection( const uint32 State, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L120 _prototype_ `FQuat Rotation(const uint32 Input);` (scope `UE::Learning::Random`)
- L122 _prototype_ `void IntArray( TLearningArrayView<1, uint32> Output, const uint32 State);` (scope `UE::Learning::Random`)
- L126 _prototype_ `void IntArray( TLearningArrayView<1, uint32> Output, const uint32 State, const FIndexSet Indices);` (scope `UE::Learning::Random`)
- L131 _prototype_ `void FloatArray( TLearningArrayView<1, float> Output, const uint32 State);` (scope `UE::Learning::Random`)
- L135 _prototype_ `void UniformArray( TLearningArrayView<1, float> Output, const uint32 State, const float Min = 0.0f, const float Max = 1.0f);` (scope `UE::Learning::Random`)
- L141 _prototype_ `void GaussianArray( TLearningArrayView<1, float> Output, const uint32 State, const float Mean = 0.0f, const float Std = 1.0f);` (scope `UE::Learning::Random`)
- L147 _prototype_ `void ClippedGaussianArray( TLearningArrayView<1, float> Output, const uint32 State, const float Mean = 0.0f, const float Std = 1.0f, const float Clip = 10.0f);` (scope `UE::Learning::Random`)
- L154 _prototype_ `void PlanarClippedGaussianArray( TLearningArrayView<1, FVector> Output, const uint32 State, const float Mean = 0.0f, const float Std = 1.0f, const float Clip = 10.0f, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L163 _prototype_ `void PlanarDirectionArray( TLearningArrayView<1, FVector> Output, const uint32 State, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L169 _prototype_ `void DistributionIndependantNormal( TLearningArrayView<1, float> Output, const uint32 State, const TLearningArrayView<1, const float> Mean, const TLearningArrayView<1, const float> LogStd, const float Scale);` (scope `UE::Learning::Random`)
- L176 _prototype_ `void DistributionIndependantNormalMasked( TLearningArrayView<1, float> Output, const uint32 State, const TLearningArrayView<1, const float> Mean, const TLearningArrayView<1, const float> LogStd, const TLearningArrayView<1, const bool> Masked, const TLearningArrayView<1, const float> MaskedValues, const float Scale);` (scope `UE::Learning::Random`)
- L185 _prototype_ `void DistributionMultinoulli( TLearningArrayView<1, float> Output, const uint32 State, const TLearningArrayView<1, const float> Logits, const float Scale);` (scope `UE::Learning::Random`)
- L191 _prototype_ `void DistributionMultinoulliMasked( TLearningArrayView<1, float> Output, const uint32 State, const TLearningArrayView<1, const float> Logits, const TLearningArrayView<1, const bool> Masked, const float Scale);` (scope `UE::Learning::Random`)
- L198 _prototype_ `void DistributionBernoulli( TLearningArrayView<1, float> Output, const uint32 State, const TLearningArrayView<1, const float> Logits, const float Scale);` (scope `UE::Learning::Random`)
- L204 _prototype_ `void DistributionBernoulliMasked( TLearningArrayView<1, float> Output, const uint32 State, const TLearningArrayView<1, const float> Logits, const TLearningArrayView<1, const bool> Masked, const float Scale);` (scope `UE::Learning::Random`)
- L211 _prototype_ `void FrameInFrameSet( int32& OutEntryIdx, int32& OutFrameIdx, const FFrameSet& FrameSet, const uint32 State);` (scope `UE::Learning::Random`)
- L217 _prototype_ `void FrameInFrameRangeSet( int32& OutEntryIdx, int32& OutRangeIdx, int32& OutRangeFrame, const FFrameRangeSet& FrameRangeSet, const uint32 State);` (scope `UE::Learning::Random`)
- L231 _prototype_ `uint32 SampleInt(uint32& State);` (scope `UE::Learning::Random`)
- L233 _prototype_ `float SampleFloat(uint32& State);` (scope `UE::Learning::Random`)
- L235 _prototype_ `int32 SampleIntInRange(uint32& State, const int32 Min, const int32 Max);` (scope `UE::Learning::Random`)
- L237 _prototype_ `float SampleUniform( uint32& State, const float Min = 0.0f, const float Max = 1.0f);` (scope `UE::Learning::Random`)
- L242 _prototype_ `float SampleGaussian( uint32& State, const float Mean = 0.0f, const float Std = 1.0f);` (scope `UE::Learning::Random`)
- L247 _prototype_ `FVector SampleVectorGaussian( uint32& State, const FVector Mean = FVector::ZeroVector, const FVector Std = FVector::OneVector);` (scope `UE::Learning::Random`)
- L252 _prototype_ `float SampleClippedGaussian( uint32& State, const float Mean = 0.0f, const float Std = 1.0f, const float Clip = 10.0f);` (scope `UE::Learning::Random`)
- L258 _prototype_ `FVector SamplePlanarUniform( uint32& State, const float Min = 0.0f, const float Max = 1.0f, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L265 _prototype_ `FVector SamplePlanarGaussian( uint32& State, const float Mean = 0.0f, const float Std = 1.0f, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L272 _prototype_ `FVector SamplePlanarClippedGaussian( uint32& State, const float Mean = 0.0f, const float Std = 1.0f, const float Clip = 10.0f, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L280 _prototype_ `FVector SamplePlanarDirection( uint32& State, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L285 _prototype_ `FQuat SampleRotation(uint32& State);` (scope `UE::Learning::Random`)
- L287 _prototype_ `void SampleIntArray( TLearningArrayView<1, uint32> Output, uint32& State);` (scope `UE::Learning::Random`)
- L291 _prototype_ `void SampleIntArray( TLearningArrayView<1, uint32> Output, uint32& State, const FIndexSet Indices);` (scope `UE::Learning::Random`)
- L296 _prototype_ `void SampleFloatArray( TLearningArrayView<1, float> Output, uint32& State);` (scope `UE::Learning::Random`)
- L300 _prototype_ `void SampleUniformArray( TLearningArrayView<1, float> Output, uint32& State, const float Min = 0.0f, const float Max = 1.0f);` (scope `UE::Learning::Random`)
- L306 _prototype_ `void SampleGaussianArray( TLearningArrayView<1, float> Output, uint32& State, const float Mean = 0.0f, const float Std = 1.0f);` (scope `UE::Learning::Random`)
- L312 _prototype_ `void SampleClippedGaussianArray( TLearningArrayView<1, float> Output, uint32& State, const float Mean = 0.0f, const float Std = 1.0f, const float Clip = 10.0f);` (scope `UE::Learning::Random`)
- L319 _prototype_ `void SamplePlanarClippedGaussianArray( TLearningArrayView<1, FVector> Output, uint32& State, const float Mean = 0.0f, const float Std = 1.0f, const float Clip = 10.0f, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L328 _prototype_ `void SamplePlanarDirectionArray( TLearningArrayView<1, FVector> Output, uint32& State, const FVector Axis0 = FVector::ForwardVector, const FVector Axis1 = FVector::RightVector);` (scope `UE::Learning::Random`)
- L334 _prototype_ `void SampleDistributionIndependantNormal( TLearningArrayView<1, float> Output, uint32& State, const TLearningArrayView<1, const float> Mean, const TLearningArrayView<1, const float> LogStd, const float Scale);` (scope `UE::Learning::Random`)
- L341 _prototype_ `void SampleDistributionIndependantNormalMasked( TLearningArrayView<1, float> Output, uint32& State, const TLearningArrayView<1, const float> Mean, const TLearningArrayView<1, const float> LogStd, const TLearningArrayView<1, const bool> Masked, const TLearningArrayView<1, const float> MaskedValues, const float Scale);` (scope `UE::Learning::Random`)
- L350 _prototype_ `void SampleDistributionMultinoulli( TLearningArrayView<1, float> Output, uint32& State, const TLearningArrayView<1, const float> Logits, const float Scale);` (scope `UE::Learning::Random`)
- L356 _prototype_ `void SampleDistributionMultinoulliMasked( TLearningArrayView<1, float> Output, uint32& State, const TLearningArrayView<1, const float> Logits, const TLearningArrayView<1, const bool> Masked, const float Scale);` (scope `UE::Learning::Random`)
- L363 _prototype_ `void SampleDistributionBernoulli( TLearningArrayView<1, float> Output, uint32& State, const TLearningArrayView<1, const float> Logits, const float Scale);` (scope `UE::Learning::Random`)
- L369 _prototype_ `void SampleDistributionBernoulliMasked( TLearningArrayView<1, float> Output, uint32& State, const TLearningArrayView<1, const float> Logits, const TLearningArrayView<1, const bool> Masked, const float Scale);` (scope `UE::Learning::Random`)
- L376 _prototype_ `void SampleFrameInFrameSet( int32& OutEntryIdx, int32& OutFrameIdx, uint32& State, const FFrameSet& FrameSet);` (scope `UE::Learning::Random`)
- L382 _prototype_ `void SampleFrameInFrameRangeSet( int32& OutEntryIdx, int32& OutRangeIdx, int32& OutRangeFrame, uint32& State, const FFrameRangeSet& FrameRangeSet);` (scope `UE::Learning::Random`)

### `Plugins/Experimental/LearningCore/Source/Learning/Public/MultiArray.h` (Public)


#### class `TMultiArray`  
`template<uint8 InDimNum, typename InElementType, typename InAllocatorType = FDefaultAllocator> class TMultiArray`  
_L53-795_
- desc: Templated dynamic multi-dimensional array A dynamically sized array of typed elements.  Makes the assumption that your elements are relocatable; i.e. that they can be transparently moved to new memory without a copy constructor.
- L56 _public member_ `static constexpr uint8 DimNum = InDimNum;`
- L57 _public typedef_ `using ElementType = InElementType;`
- L58 _public typedef_ `using AllocatorType = InAllocatorType;`
- L60 _public typedef_ `using ElementAllocatorType = std::conditional_t< AllocatorType::NeedsElementType, typename AllocatorType::template ForElementType<ElementType>, typename AllocatorType::ForAnyElementType >;`
- L75 _public function_ `inline TMultiArrayView<DimNum - 1, ElementType> operator[](int64 Index)` — Array bracket operator. Returns reference to element at given index. @returns Reference to indexed element.
- L95 _public function_ `inline TMultiArrayView<DimNum - 1, const ElementType> operator[](int64 Index) const` — Array bracket operator. Returns reference to element at given index. Const version of the above. @returns Reference to indexed element.
- L113 _public function_ `inline TMultiArrayView<1, ElementType> Flatten()` — Flattens the array view into a single dimension. @returns Flattened array view.
- L123 _public function_ `inline TMultiArrayView<1, const ElementType> Flatten() const` — Flattens the array view into a single dimension. @returns Flattened array view.
- L134 _public function_ `inline TMultiArrayView<DimNum - 1, ElementType> Flatten(uint8 Dimension)` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L163 _public function_ `inline TMultiArrayView<DimNum - 1, const ElementType> Flatten(uint8 Dimension) const` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L193 _public function_ `template<uint8 Dimension> inline TMultiArrayView<DimNum - 1, ElementType> Flatten()` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L223 _public function_ `template<uint8 Dimension> inline TMultiArrayView<DimNum - 1, const ElementType> Flatten() const` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L252 _public prototype_ `inline TMultiArray() = default;` — Constructor, initializes element number counters.
- L260 _public function_ `inline TMultiArray(const ElementType* Ptr, TMultiArrayShape<DimNum> Shape)` — Constructor from a raw array of elements. @param Ptr   A pointer to an array of elements to copy. @param Nums The number of elements on each dimension.
- L268 _public function_ `template <typename OtherElementType> inline explicit TMultiArray(const TMultiArrayView<DimNum, OtherElementType>& Other) : TMultiArray(Other.GetData(), Other.Shape())`
- L281 _public function_ `inline explicit TMultiArray(const TMultiArray<DimNum, OtherElementType, OtherAllocator>& Other)`
- L291 _public function_ `inline TMultiArray(const TMultiArray& Other)` — Copy constructor. Use the common routine to perform the copy. @param Other The source array to copy.
- L305 _public function_ `template<typename OtherAllocatorType> TMultiArray& operator=(const TMultiArray<DimNum, ElementType, OtherAllocatorType>& Other)` — Assignment operator. First deletes all currently contained elements and then copies from other array. AllocatorType changing version. @param Other The source array to assign from.
- L318 _public function_ `TMultiArray& operator=(const TMultiArray& Other)` — Assignment operator. First deletes all currently contained elements and then copies from other array. @param Other The source array to assign from.
- L329 _public prototype_ `template <typename OtherElementType> TMultiArray& operator=(const TMultiArrayView<DimNum, OtherElementType>& Other);`
- L342 _private function_ `template <typename FromArrayType, typename ToArrayType> static inline void MoveOrCopy(ToArrayType& ToArray, FromArrayType& FromArray)` — Moves or copies array. Depends on the array type traits. This override copies. @param ToArray Array to move into. @param FromArray Array to move from.
- L353 _public function_ `inline TMultiArray(TMultiArray&& Other)` — Move constructor. @param Other Array to move from.
- L368 _public function_ `inline explicit TMultiArray(TMultiArray<DimNum, OtherElementType, OtherAllocator>&& Other)`
- L378 _public function_ `TMultiArray& operator=(TMultiArray&& Other)` — Move assignment operator. @param Other Array to assign and move from.
- L389 _public function_ `~TMultiArray()` — Destructor.
- L402 _public function_ `inline ElementType* GetData()` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if empty
- L412 _public function_ `inline const ElementType* GetData() const` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if empty
- L421 _public function_ `inline ElementType* begin()` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L422 _public function_ `inline ElementType* end()`
- L428 _public function_ `inline const ElementType* begin() const` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L429 _public function_ `inline const ElementType* end() const`
- L436 _public function_ `inline uint32 GetTypeSize() const` — Helper function returning the size of the inner type. @returns Size in bytes of array type.
- L445 _public function_ `inline void CheckInvariants() const` — Checks array invariants: if array size is greater than zero and less than maximum.
- L458 _public function_ `inline void DimensionCheck(uint8 Dimension) const` — Checks if a dimension is within the allowed number of dimensions @param Dimension Dimension of the array.
- L469 _public function_ `inline void RangeCheck(uint8 Dimension, int64 Index) const` — Checks if index is in dimension range. @param Dimension Dimension of the array. @param Index Index to check.
- L485 _public function_ `inline void SliceRangeCheck(uint8 Dimension, int64 Index, int64 InNum) const` — Checks if a slice range [Index, Index+InNum) is in dimension range. Length is 0 is allowed on empty dimensions; Index must be 0 in that case. @param Dimension Dimension of the array. @param Index Starting index of the slice. @param InNum Length of the slice.
- L500 _public function_ `bool IsEmpty() const` — Returns true if the array is empty and contains no elements. @returns True if the array is empty. @see Num
- L512 _public function_ `bool IsEmpty(uint8 Dimension) const` — Returns true if the dimension is empty and contains no elements. @param Dimension Dimension of the array. @returns True if the dimension is empty. @see Num
- L524 _public function_ `inline uint8 Rank() const` — Returns number of dimensions. @returns Number of dimensions in array.
- L534 _public function_ `inline int64 Num() const` — Returns total number of elements @returns Total number of elements in array.
- L544 _public function_ `inline int64 NumBytes() const` — Returns the total number of bytes used by the array @returns Total number of bytes used by the array.
- L555 _public function_ `template<uint8 InDimIdx> inline int64 Num() const` — Returns number of elements in a dimension. @returns Number of elements in array.
- L567 _public function_ `inline int64 Num(uint8 Dimension) const` — Returns number of elements in a dimension. @param Dimension Dimension of the array. @returns Number of elements in array.
- L579 _public function_ `inline TMultiArrayShape<DimNum> Shape() const` — Returns the number of elements in each dimension. @returns Number of elements in each dimension.
- L590 _public function_ `inline int64 Stride(uint8 Dimension) const` — Returns the stride for a dimension. @param Dimension Dimension of the array. @returns Stride of that dimension.
- L609 _public function_ `[[nodiscard]] inline TMultiArrayView<DimNum, ElementType> Slice(int64 Index, int64 InNum)` — Returns a sliced view. Slicing outside of the range of the view is illegal. @param Index Starting index of the new view @param InNum Number of elements in the new view @returns Sliced view
- L624 _public function_ `[[nodiscard]] inline TMultiArrayView<DimNum, const ElementType> Slice(int64 Index, int64 InNum) const` — Returns a sliced view. Slicing outside of the range of the view is illegal. @param Index Starting index of the new view @param InNum Number of elements in the new view @returns Sliced view
- L638 _public function_ `template <typename ComparisonType> bool Contains(const ComparisonType& Item) const` — Checks if this array contains the element. @returns	True if found. False otherwise.
- L655 _public function_ `void Empty()` — Empties the array. It calls the destructors on held items if needed.
- L668 _public function_ `void SetNum(TMultiArrayShape<DimNum> NewShape)` — Resizes array to given number of elements. @param NewShape New shape of the array.
- L692 _public function_ `void SetNumZeroed(TMultiArrayShape<DimNum> NewShape)` — Resizes array to given number of elements. New elements will be zeroed. @param NewShape New shape of the array.
- L716 _public function_ `void SetNumUninitialized(TMultiArrayShape<DimNum> NewShape)` — Resizes array to given number of elements. New elements will be uninitialized. @param NewShape New shape of the array.
- L735 _private function_ `void AllocatorResizeAllocation(int64 CurrentNum, int64 NewNum)`
- L755 _private function_ `template <typename OtherElementType> void CopyToEmpty(const OtherElementType* OtherData, TMultiArrayShape<DimNum> OtherShape)` — Copies data from one array into this array. Uses the fast path if the data in question does not need a constructor. @param OtherData A pointer to the data to copy @param OtherNums The dimensions of the data to copy
- L776 _public function_ `const ElementAllocatorType& GetAllocatorInstance() const`
- L777 _public function_ `ElementAllocatorType& GetAllocatorInstance()`
- L781 _public function_ `inline operator TMultiArrayView<DimNum, ElementType>()`
- L786 _public function_ `inline operator TMultiArrayView<DimNum, const ElementType>() const`
- L793 _protected member_ `ElementAllocatorType AllocatorInstance;`
- L794 _protected member_ `TMultiArrayShape<DimNum> ArrayShape;`
- L805 _public member_ `static constexpr uint8 DimNum = 1;`
- L818 _public function_ `TMultiArray(std::initializer_list<InElementType> InitList)` — Initializer list constructor
- L832 _public function_ `TMultiArray& operator=(std::initializer_list<InElementType> InitList)` — Initializer list assignment operator. First deletes all currently contained elements and then copies from initializer list. @param InitList The initializer_list to copy from.
- L847 _public function_ `inline ElementType& operator[](int64 Index)` — Array bracket operator. Returns reference to element at given index. @returns Reference to indexed element.
- L860 _public function_ `inline const ElementType& operator[](int64 Index) const` — Array bracket operator. Returns reference to element at given index. Const version of the above. @returns Reference to indexed element.
- L887 _public function_ `inline TArrayView<ElementType> ArrayView()` — Explicit conversion to TArrayView.
- L893 _public function_ `inline TArrayView<const ElementType> ArrayView() const` — Explicit conversion to TArrayView.
- L899 _public function_ `inline operator TArrayView<ElementType>()` — Implicit cast to TArrayView.
- L905 _public function_ `inline operator TArrayView<const ElementType>() const` — Implicit cast to TArrayView.
- L931 _public function_ `template <typename OtherElementType> explicit TMultiArray(const TMultiArrayView<DimNum, OtherElementType>& Other) : TMultiArray(Other.GetData(), Other.Shape())`

#### class `TMultiArray`  
`template<typename InElementType, typename InAllocatorType> class TMultiArray<1, InElementType, InAllocatorType>`  
_L802-1460_
- desc: Specialization for single dimensional MultiArray
- L56 _public member_ `static constexpr uint8 DimNum = InDimNum;`
- L57 _public typedef_ `using ElementType = InElementType;`
- L58 _public typedef_ `using AllocatorType = InAllocatorType;`
- L60 _public typedef_ `using ElementAllocatorType = std::conditional_t< AllocatorType::NeedsElementType, typename AllocatorType::template ForElementType<ElementType>, typename AllocatorType::ForAnyElementType >;`
- L75 _public function_ `inline TMultiArrayView<DimNum - 1, ElementType> operator[](int64 Index)` — Array bracket operator. Returns reference to element at given index. @returns Reference to indexed element.
- L95 _public function_ `inline TMultiArrayView<DimNum - 1, const ElementType> operator[](int64 Index) const` — Array bracket operator. Returns reference to element at given index. Const version of the above. @returns Reference to indexed element.
- L113 _public function_ `inline TMultiArrayView<1, ElementType> Flatten()` — Flattens the array view into a single dimension. @returns Flattened array view.
- L123 _public function_ `inline TMultiArrayView<1, const ElementType> Flatten() const` — Flattens the array view into a single dimension. @returns Flattened array view.
- L134 _public function_ `inline TMultiArrayView<DimNum - 1, ElementType> Flatten(uint8 Dimension)` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L163 _public function_ `inline TMultiArrayView<DimNum - 1, const ElementType> Flatten(uint8 Dimension) const` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L193 _public function_ `template<uint8 Dimension> inline TMultiArrayView<DimNum - 1, ElementType> Flatten()` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L223 _public function_ `template<uint8 Dimension> inline TMultiArrayView<DimNum - 1, const ElementType> Flatten() const` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L252 _public prototype_ `inline TMultiArray() = default;` — Constructor, initializes element number counters.
- L260 _public function_ `inline TMultiArray(const ElementType* Ptr, TMultiArrayShape<DimNum> Shape)` — Constructor from a raw array of elements. @param Ptr   A pointer to an array of elements to copy. @param Nums The number of elements on each dimension.
- L268 _public function_ `template <typename OtherElementType> inline explicit TMultiArray(const TMultiArrayView<DimNum, OtherElementType>& Other) : TMultiArray(Other.GetData(), Other.Shape())`
- L281 _public function_ `inline explicit TMultiArray(const TMultiArray<DimNum, OtherElementType, OtherAllocator>& Other)`
- L291 _public function_ `inline TMultiArray(const TMultiArray& Other)` — Copy constructor. Use the common routine to perform the copy. @param Other The source array to copy.
- L305 _public function_ `template<typename OtherAllocatorType> TMultiArray& operator=(const TMultiArray<DimNum, ElementType, OtherAllocatorType>& Other)` — Assignment operator. First deletes all currently contained elements and then copies from other array. AllocatorType changing version. @param Other The source array to assign from.
- L318 _public function_ `TMultiArray& operator=(const TMultiArray& Other)` — Assignment operator. First deletes all currently contained elements and then copies from other array. @param Other The source array to assign from.
- L329 _public prototype_ `template <typename OtherElementType> TMultiArray& operator=(const TMultiArrayView<DimNum, OtherElementType>& Other);`
- L342 _private function_ `template <typename FromArrayType, typename ToArrayType> static inline void MoveOrCopy(ToArrayType& ToArray, FromArrayType& FromArray)` — Moves or copies array. Depends on the array type traits. This override copies. @param ToArray Array to move into. @param FromArray Array to move from.
- L353 _public function_ `inline TMultiArray(TMultiArray&& Other)` — Move constructor. @param Other Array to move from.
- L368 _public function_ `inline explicit TMultiArray(TMultiArray<DimNum, OtherElementType, OtherAllocator>&& Other)`
- L378 _public function_ `TMultiArray& operator=(TMultiArray&& Other)` — Move assignment operator. @param Other Array to assign and move from.
- L389 _public function_ `~TMultiArray()` — Destructor.
- L402 _public function_ `inline ElementType* GetData()` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if empty
- L412 _public function_ `inline const ElementType* GetData() const` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if empty
- L421 _public function_ `inline ElementType* begin()` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L422 _public function_ `inline ElementType* end()`
- L428 _public function_ `inline const ElementType* begin() const` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L429 _public function_ `inline const ElementType* end() const`
- L436 _public function_ `inline uint32 GetTypeSize() const` — Helper function returning the size of the inner type. @returns Size in bytes of array type.
- L445 _public function_ `inline void CheckInvariants() const` — Checks array invariants: if array size is greater than zero and less than maximum.
- L458 _public function_ `inline void DimensionCheck(uint8 Dimension) const` — Checks if a dimension is within the allowed number of dimensions @param Dimension Dimension of the array.
- L469 _public function_ `inline void RangeCheck(uint8 Dimension, int64 Index) const` — Checks if index is in dimension range. @param Dimension Dimension of the array. @param Index Index to check.
- L485 _public function_ `inline void SliceRangeCheck(uint8 Dimension, int64 Index, int64 InNum) const` — Checks if a slice range [Index, Index+InNum) is in dimension range. Length is 0 is allowed on empty dimensions; Index must be 0 in that case. @param Dimension Dimension of the array. @param Index Starting index of the slice. @param InNum Length of the slice.
- L500 _public function_ `bool IsEmpty() const` — Returns true if the array is empty and contains no elements. @returns True if the array is empty. @see Num
- L512 _public function_ `bool IsEmpty(uint8 Dimension) const` — Returns true if the dimension is empty and contains no elements. @param Dimension Dimension of the array. @returns True if the dimension is empty. @see Num
- L524 _public function_ `inline uint8 Rank() const` — Returns number of dimensions. @returns Number of dimensions in array.
- L534 _public function_ `inline int64 Num() const` — Returns total number of elements @returns Total number of elements in array.
- L544 _public function_ `inline int64 NumBytes() const` — Returns the total number of bytes used by the array @returns Total number of bytes used by the array.
- L555 _public function_ `template<uint8 InDimIdx> inline int64 Num() const` — Returns number of elements in a dimension. @returns Number of elements in array.
- L567 _public function_ `inline int64 Num(uint8 Dimension) const` — Returns number of elements in a dimension. @param Dimension Dimension of the array. @returns Number of elements in array.
- L579 _public function_ `inline TMultiArrayShape<DimNum> Shape() const` — Returns the number of elements in each dimension. @returns Number of elements in each dimension.
- L590 _public function_ `inline int64 Stride(uint8 Dimension) const` — Returns the stride for a dimension. @param Dimension Dimension of the array. @returns Stride of that dimension.
- L609 _public function_ `[[nodiscard]] inline TMultiArrayView<DimNum, ElementType> Slice(int64 Index, int64 InNum)` — Returns a sliced view. Slicing outside of the range of the view is illegal. @param Index Starting index of the new view @param InNum Number of elements in the new view @returns Sliced view
- L624 _public function_ `[[nodiscard]] inline TMultiArrayView<DimNum, const ElementType> Slice(int64 Index, int64 InNum) const` — Returns a sliced view. Slicing outside of the range of the view is illegal. @param Index Starting index of the new view @param InNum Number of elements in the new view @returns Sliced view
- L638 _public function_ `template <typename ComparisonType> bool Contains(const ComparisonType& Item) const` — Checks if this array contains the element. @returns	True if found. False otherwise.
- L655 _public function_ `void Empty()` — Empties the array. It calls the destructors on held items if needed.
- L668 _public function_ `void SetNum(TMultiArrayShape<DimNum> NewShape)` — Resizes array to given number of elements. @param NewShape New shape of the array.
- L692 _public function_ `void SetNumZeroed(TMultiArrayShape<DimNum> NewShape)` — Resizes array to given number of elements. New elements will be zeroed. @param NewShape New shape of the array.
- L716 _public function_ `void SetNumUninitialized(TMultiArrayShape<DimNum> NewShape)` — Resizes array to given number of elements. New elements will be uninitialized. @param NewShape New shape of the array.
- L735 _private function_ `void AllocatorResizeAllocation(int64 CurrentNum, int64 NewNum)`
- L755 _private function_ `template <typename OtherElementType> void CopyToEmpty(const OtherElementType* OtherData, TMultiArrayShape<DimNum> OtherShape)` — Copies data from one array into this array. Uses the fast path if the data in question does not need a constructor. @param OtherData A pointer to the data to copy @param OtherNums The dimensions of the data to copy
- L776 _public function_ `const ElementAllocatorType& GetAllocatorInstance() const`
- L777 _public function_ `ElementAllocatorType& GetAllocatorInstance()`
- L781 _public function_ `inline operator TMultiArrayView<DimNum, ElementType>()`
- L786 _public function_ `inline operator TMultiArrayView<DimNum, const ElementType>() const`
- L793 _protected member_ `ElementAllocatorType AllocatorInstance;`
- L794 _protected member_ `TMultiArrayShape<DimNum> ArrayShape;`
- L805 _public member_ `static constexpr uint8 DimNum = 1;`
- L818 _public function_ `TMultiArray(std::initializer_list<InElementType> InitList)` — Initializer list constructor
- L832 _public function_ `TMultiArray& operator=(std::initializer_list<InElementType> InitList)` — Initializer list assignment operator. First deletes all currently contained elements and then copies from initializer list. @param InitList The initializer_list to copy from.
- L847 _public function_ `inline ElementType& operator[](int64 Index)` — Array bracket operator. Returns reference to element at given index. @returns Reference to indexed element.
- L860 _public function_ `inline const ElementType& operator[](int64 Index) const` — Array bracket operator. Returns reference to element at given index. Const version of the above. @returns Reference to indexed element.
- L887 _public function_ `inline TArrayView<ElementType> ArrayView()` — Explicit conversion to TArrayView.
- L893 _public function_ `inline TArrayView<const ElementType> ArrayView() const` — Explicit conversion to TArrayView.
- L899 _public function_ `inline operator TArrayView<ElementType>()` — Implicit cast to TArrayView.
- L905 _public function_ `inline operator TArrayView<const ElementType>() const` — Implicit cast to TArrayView.
- L931 _public function_ `template <typename OtherElementType> explicit TMultiArray(const TMultiArrayView<DimNum, OtherElementType>& Other) : TMultiArray(Other.GetData(), Other.Shape())`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MultiArray` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::MultiArray`)
- L41 _variable_ `template <typename DestType, typename SourceType> constexpr bool TMultiArrayElementsAreCompatible_V = std::is_same_v<DestType, std::decay_t<SourceType>> || std::is_constructible_v<DestType, SourceType>;` (scope `UE::MultiArray::Private`) — Copied from Core/Public/Containers/Array.h Assume elements are compatible with themselves - avoids problems with generated copy constructors of arrays of forwarded types, e.g.: struct FThing; struct FOuter { TMultiArray<2, FThing> Arr; // this will cause errors without this workaround }; This should be changed to use std::disjunction and std::is_constructible, and the usage changed to use ::value instead of ::Value, when std::disjunction (C++17) is available everywhere.

### `Plugins/Experimental/LearningCore/Source/Learning/Public/MultiArrayView.h` (Public)


#### struct `UE::MultiArrayView::Private::TIsCompatibleRangeType`  
`template <typename RangeType, typename ElementType> struct TIsCompatibleRangeType`  
_L58-67_
- desc: Copied from Core/Public/Containers/ArrayView.h Trait testing whether a type is compatible with the view type
- L60 _public member_ `static constexpr bool Value = TIsCompatibleElementType_V<std::remove_pointer_t<decltype(GetData(DeclVal<RangeType&>()))>, ElementType>;`
- L63 _public function_ `template <typename T> static decltype(auto) GetData(T&& Arg)`

#### struct `UE::MultiArrayView::Private::TIsReinterpretableRangeType`  
`template <typename RangeType, typename ElementType> struct TIsReinterpretableRangeType`  
_L75-91_
- desc: Copied from Core/Public/Containers/ArrayView.h Trait testing whether a type is reinterpretable in a way that permits use with the view type
- L78 _private typedef_ `using NaturalElementType = std::remove_pointer_t<decltype(GetData(DeclVal<RangeType&>()))>;`
- L81 _public member_ `static constexpr bool Value = !std::is_same_v<typename TContainerElementTypeCompatibility<NaturalElementType>::ReinterpretType, NaturalElementType> && TIsCompatibleElementType_V<typename TContainerElementTypeCompatibility<NaturalElementType>::ReinterpretType, ElementType>;`
- L87 _public function_ `template <typename T> static decltype(auto) GetData(T&& Arg)`

#### class `TMultiArrayShape`  
`template<uint8 InDimNum> class TMultiArrayShape`  
_L95-155_
- L98 _public member_ `static constexpr uint8 DimNum = InDimNum;`
- L104 _public prototype_ `TMultiArrayShape() = default;`
- L106 _public function_ `TMultiArrayShape(std::initializer_list<int64> InNums)`
- L118 _public function_ `TMultiArrayShape(const int64* InNums)`
- L126 _public function_ `int64& operator[](uint8 Dimension)`
- L131 _public function_ `const int64& operator[](uint8 Dimension) const`
- L136 _public function_ `int64 Total() const`
- L154 _private member_ `int64 Nums[DimNum] = { 0 };`

#### class `TMultiArrayView`  
`template<uint8 InDimNum, typename InElementType> class TMultiArrayView`  
_L165-521_
- desc: Templated fixed-size view of multi-dimensional array A statically sized view of a multi-dimensional array of typed elements. @see TArrayView
- L168 _public member_ `static constexpr uint8 DimNum = InDimNum;`
- L169 _public typedef_ `using ElementType = InElementType;`
- L178 _public function_ `TMultiArrayView() : DataPtr(nullptr)` — Constructor.
- L186 _public function_ `inline TMultiArrayView(ElementType* InData, TMultiArrayShape<DimNum> InShape) : DataPtr(InData) , ArrayShape(InShape)` — Construct a view of an arbitrary pointer @param InData	The data to view @param InShape	The number of elements on each dimension
- L198 _public function_ `inline TMultiArrayView<DimNum - 1, ElementType> operator[](int64 Index) const` — Array bracket operator. Returns reference to sub-view at given index. @returns Reference to indexed element.
- L216 _public function_ `inline TMultiArrayView<1, ElementType> Flatten() const` — Flattens the array view into a single dimension. @returns Flattened array view.
- L227 _public function_ `inline TMultiArrayView<DimNum - 1, ElementType> Flatten(uint8 Dimension) const` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L257 _public function_ `template<uint8 Dimension> inline TMultiArrayView<DimNum - 1, ElementType> Flatten() const` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L287 _public function_ `inline ElementType* GetData() const` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if empty
- L297 _public function_ `inline ElementType* begin() const` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L298 _public function_ `inline ElementType* end() const`
- L305 _public function_ `inline static constexpr size_t GetTypeSize()` — Helper function returning the size of the inner type. @returns Size in bytes of array type.
- L313 _public function_ `inline static constexpr size_t GetTypeAlignment()` — Helper function returning the alignment of the inner type.
- L321 _public function_ `inline void CheckInvariants() const` — Checks array invariants: if array size is greater than zero on each dimension
- L334 _public function_ `inline void DimensionCheck(uint8 Dimension) const` — Checks if a dimension is within the allowed number of dimensions @param Dimension Dimension of the array.
- L345 _public function_ `inline void RangeCheck(uint8 Dimension, int64 Index) const` — Checks if index is in dimension range. @param Dimension Dimension of the array. @param Index Index to check.
- L361 _public function_ `inline void SliceRangeCheck(uint8 Dimension, int64 Index, int64 InNum) const` — Checks if a slice range [Index, Index+InNum) is in dimension range. Length is 0 is allowed on empty dimensions; Index must be 0 in that case. @param Dimension Dimension of the array. @param Index Starting index of the slice. @param InNum Length of the slice.
- L376 _public function_ `bool IsEmpty() const` — Returns true if the array is empty and contains no elements. @returns True if the array is empty. @see Num
- L388 _public function_ `bool IsEmpty(uint8 Dimension) const` — Returns true if the dimension is empty and contains no elements. @param Dimension Dimension of the array. @returns True if the dimension is empty. @see Num
- L400 _public function_ `inline uint8 Rank() const` — Returns the number of dimensions. @returns Number of dimensions in array.
- L410 _public function_ `inline int64 Num() const` — Returns the total number of elements @returns Total number of elements in array.
- L420 _public function_ `inline int64 NumBytes() const` — Returns the total number of bytes used by the array @returns Total number of bytes used by the array.
- L431 _public function_ `template<uint8 InDimIdx> inline int64 Num() const` — Returns the number of elements in a dimension. @returns Number of elements in array.
- L443 _public function_ `inline int64 Num(uint8 Dimension) const` — Returns the number of elements in a dimension. @param Dimension Dimension of the array. @returns Number of elements in array.
- L455 _public function_ `inline TMultiArrayShape<DimNum> Shape() const` — Returns the number of elements in each dimension. @returns Number of elements in each dimension.
- L466 _public function_ `inline int64 Stride(uint8 Dimension) const` — Returns the stride for a dimension. @param Dimension Dimension of the array. @returns Stride of that dimension.
- L485 _public function_ `[[nodiscard]] inline TMultiArrayView Slice(int64 Index, int64 InNum) const` — Returns a sliced view. Slicing outside of the range of the view is illegal. @param Index Starting index of the new view @param InNum Number of elements in the new view @returns Sliced view
- L499 _public function_ `template <typename ComparisonType> bool Contains(const ComparisonType& Item) const` — Checks if this array contains the element. @returns	True if found. False otherwise.
- L512 _public function_ `inline operator TMultiArrayView<DimNum, const ElementType>() const` — Implicit cast for const.
- L519 _private member_ `ElementType* DataPtr;`
- L520 _private member_ `TMultiArrayShape<DimNum> ArrayShape;`
- L531 _public member_ `static constexpr uint8 DimNum = 1;`
- L541 _private typedef_ `template <typename T> using TIsCompatibleRangeType = UE::MultiArrayView::Private::TIsCompatibleRangeType<T, ElementType>;`
- L544 _private typedef_ `template <typename T> using TIsReinterpretableRangeType = UE::MultiArrayView::Private::TIsReinterpretableRangeType<T, ElementType>;`
- L565 _public function_ `inline TMultiArrayView(OtherRangeType&& Other) : DataPtr(std::conditional_t< TIsCompatibleRangeType<OtherRangeType>::Value, TIsCompatibleRangeType<OtherRangeType>, TIsReinterpretableRangeType<OtherRangeType> >::GetData(Forward<OtherRangeType>(Other)))`
- L600 _public function_ `inline TMultiArrayView(OtherElementType* InData, int64 InNum) : DataPtr(InData)`
- L612 _public function_ `inline TMultiArrayView(std::initializer_list<ElementType> List) : DataPtr(UE::MultiArrayView::Private::GetDataHelper(List))` — Construct a view of an initializer list. The caller is responsible for ensuring that the view does not outlive the initializer list.
- L626 _public function_ `inline ElementType& operator[](int64 Index) const` — Array bracket operator. Returns a reference to the element at given index. @returns Reference to indexed element.
- L633 _public function_ `inline TArrayView<ElementType> ArrayView()` — Explicit conversion to TArrayView.
- L639 _public function_ `inline TArrayView<const ElementType> ArrayView() const` — Explicit conversion to TArrayView.
- L645 _public function_ `inline operator TArrayView<ElementType>()` — Implicit cast to TArrayView.
- L651 _public function_ `inline operator TArrayView<const ElementType>() const` — Implicit cast to TArrayView.

#### class `TMultiArrayView`  
`template<typename InElementType> class TMultiArrayView<1, InElementType>`  
_L528-896_
- desc: Specialization for single dimensional MultiArrayView
- L168 _public member_ `static constexpr uint8 DimNum = InDimNum;`
- L169 _public typedef_ `using ElementType = InElementType;`
- L178 _public function_ `TMultiArrayView() : DataPtr(nullptr)` — Constructor.
- L186 _public function_ `inline TMultiArrayView(ElementType* InData, TMultiArrayShape<DimNum> InShape) : DataPtr(InData) , ArrayShape(InShape)` — Construct a view of an arbitrary pointer @param InData	The data to view @param InShape	The number of elements on each dimension
- L198 _public function_ `inline TMultiArrayView<DimNum - 1, ElementType> operator[](int64 Index) const` — Array bracket operator. Returns reference to sub-view at given index. @returns Reference to indexed element.
- L216 _public function_ `inline TMultiArrayView<1, ElementType> Flatten() const` — Flattens the array view into a single dimension. @returns Flattened array view.
- L227 _public function_ `inline TMultiArrayView<DimNum - 1, ElementType> Flatten(uint8 Dimension) const` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L257 _public function_ `template<uint8 Dimension> inline TMultiArrayView<DimNum - 1, ElementType> Flatten() const` — Flattens the array on a given dimension, merging that dimension and the following one. e.g. a 3D MultiArrayView with shape [10, 5, 3] flattened on dimension 0 will become a 2D MultiArrayView with shape [10 * 5, 3] @returns View flattened on the given dimension.
- L287 _public function_ `inline ElementType* GetData() const` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if empty
- L297 _public function_ `inline ElementType* begin() const` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L298 _public function_ `inline ElementType* end() const`
- L305 _public function_ `inline static constexpr size_t GetTypeSize()` — Helper function returning the size of the inner type. @returns Size in bytes of array type.
- L313 _public function_ `inline static constexpr size_t GetTypeAlignment()` — Helper function returning the alignment of the inner type.
- L321 _public function_ `inline void CheckInvariants() const` — Checks array invariants: if array size is greater than zero on each dimension
- L334 _public function_ `inline void DimensionCheck(uint8 Dimension) const` — Checks if a dimension is within the allowed number of dimensions @param Dimension Dimension of the array.
- L345 _public function_ `inline void RangeCheck(uint8 Dimension, int64 Index) const` — Checks if index is in dimension range. @param Dimension Dimension of the array. @param Index Index to check.
- L361 _public function_ `inline void SliceRangeCheck(uint8 Dimension, int64 Index, int64 InNum) const` — Checks if a slice range [Index, Index+InNum) is in dimension range. Length is 0 is allowed on empty dimensions; Index must be 0 in that case. @param Dimension Dimension of the array. @param Index Starting index of the slice. @param InNum Length of the slice.
- L376 _public function_ `bool IsEmpty() const` — Returns true if the array is empty and contains no elements. @returns True if the array is empty. @see Num
- L388 _public function_ `bool IsEmpty(uint8 Dimension) const` — Returns true if the dimension is empty and contains no elements. @param Dimension Dimension of the array. @returns True if the dimension is empty. @see Num
- L400 _public function_ `inline uint8 Rank() const` — Returns the number of dimensions. @returns Number of dimensions in array.
- L410 _public function_ `inline int64 Num() const` — Returns the total number of elements @returns Total number of elements in array.
- L420 _public function_ `inline int64 NumBytes() const` — Returns the total number of bytes used by the array @returns Total number of bytes used by the array.
- L431 _public function_ `template<uint8 InDimIdx> inline int64 Num() const` — Returns the number of elements in a dimension. @returns Number of elements in array.
- L443 _public function_ `inline int64 Num(uint8 Dimension) const` — Returns the number of elements in a dimension. @param Dimension Dimension of the array. @returns Number of elements in array.
- L455 _public function_ `inline TMultiArrayShape<DimNum> Shape() const` — Returns the number of elements in each dimension. @returns Number of elements in each dimension.
- L466 _public function_ `inline int64 Stride(uint8 Dimension) const` — Returns the stride for a dimension. @param Dimension Dimension of the array. @returns Stride of that dimension.
- L485 _public function_ `[[nodiscard]] inline TMultiArrayView Slice(int64 Index, int64 InNum) const` — Returns a sliced view. Slicing outside of the range of the view is illegal. @param Index Starting index of the new view @param InNum Number of elements in the new view @returns Sliced view
- L499 _public function_ `template <typename ComparisonType> bool Contains(const ComparisonType& Item) const` — Checks if this array contains the element. @returns	True if found. False otherwise.
- L512 _public function_ `inline operator TMultiArrayView<DimNum, const ElementType>() const` — Implicit cast for const.
- L519 _private member_ `ElementType* DataPtr;`
- L520 _private member_ `TMultiArrayShape<DimNum> ArrayShape;`
- L531 _public member_ `static constexpr uint8 DimNum = 1;`
- L541 _private typedef_ `template <typename T> using TIsCompatibleRangeType = UE::MultiArrayView::Private::TIsCompatibleRangeType<T, ElementType>;`
- L544 _private typedef_ `template <typename T> using TIsReinterpretableRangeType = UE::MultiArrayView::Private::TIsReinterpretableRangeType<T, ElementType>;`
- L565 _public function_ `inline TMultiArrayView(OtherRangeType&& Other) : DataPtr(std::conditional_t< TIsCompatibleRangeType<OtherRangeType>::Value, TIsCompatibleRangeType<OtherRangeType>, TIsReinterpretableRangeType<OtherRangeType> >::GetData(Forward<OtherRangeType>(Other)))`
- L600 _public function_ `inline TMultiArrayView(OtherElementType* InData, int64 InNum) : DataPtr(InData)`
- L612 _public function_ `inline TMultiArrayView(std::initializer_list<ElementType> List) : DataPtr(UE::MultiArrayView::Private::GetDataHelper(List))` — Construct a view of an initializer list. The caller is responsible for ensuring that the view does not outlive the initializer list.
- L626 _public function_ `inline ElementType& operator[](int64 Index) const` — Array bracket operator. Returns a reference to the element at given index. @returns Reference to indexed element.
- L633 _public function_ `inline TArrayView<ElementType> ArrayView()` — Explicit conversion to TArrayView.
- L639 _public function_ `inline TArrayView<const ElementType> ArrayView() const` — Explicit conversion to TArrayView.
- L645 _public function_ `inline operator TArrayView<ElementType>()` — Implicit cast to TArrayView.
- L651 _public function_ `inline operator TArrayView<const ElementType>() const` — Implicit cast to TArrayView.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiArrayView` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::MultiArrayView`)
- L25 _variable_ `template <typename T, typename ElementType> constexpr bool TIsCompatibleElementType_V = std::is_convertible_v<T**, ElementType* const*>;` (scope `UE::MultiArrayView::Private`) — Copied from Core/Public/Containers/ArrayView.h Trait testing whether a type is compatible with the view type The extra stars here are *IMPORTANT* They prevent TMultiArrayView<Base>(TArray<Derived>&) from compiling!
- L32 _function_ `template <typename T> inline decltype(auto) GetDataHelper(T&& Arg)` (scope `UE::MultiArrayView::Private`) — Copied from Core/Public/Containers/ArrayView.h Simply forwards to an unqualified GetData(), but can be called from within TArrayView where GetData() is already a member and so hides any others.
- L41 _function_ `template <typename T> inline decltype(auto) GetReinterpretedDataHelper(T&& Arg)` (scope `UE::MultiArrayView::Private`) — Copied from Core/Public/Containers/ArrayView.h Gets the data from the passed argument and proceeds to reinterpret the resulting elements
- L44 _typedef_ `using NaturalElementType = std::remove_pointer_t<decltype(NaturalPtr)>;` (scope `UE::MultiArrayView::Private::GetReinterpretedDataHelper`)
- L899 _typedef_ `template<uint8 InDimNum, typename InElementType> using TConstMultiArrayView = TMultiArrayView<InDimNum, const InElementType>;`
