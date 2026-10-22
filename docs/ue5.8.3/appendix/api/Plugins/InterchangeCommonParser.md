# Plugins / InterchangeCommonParser

- module root: `Plugins/Interchange/Runtime/Source/Parsers/CommonParser`
- headers: 2; symbols: 87
- symbol kinds: class=1, enum=3, enumerator=12, function=9, macro=1, member=34, namespace=3, prototype=18, struct=6
- PrivateDependencyModuleNames: Engine, Json
- PublicDependencyModuleNames: Core, CoreUObject, InterchangeCore, InterchangeNodes

### `Plugins/Interchange/Runtime/Source/Parsers/CommonParser/Public/InterchangeCommonAnimationPayload.h` (Public)


#### struct `UE::Interchange::FAnimationPayloadData`  
`struct FAnimationPayloadData`  
_L25-65_
- L27 _public member_ `FString SceneNodeUniqueID;`
- L31 _public member_ `TArray<FRichCurve> Curves;` — CURVE
- L34 _public member_ `TArray<FString> InbetweenCurveNames;` — In-between blend shape data
- L35 _public member_ `TArray<float> InbetweenFullWeights;`
- L38 _public member_ `TArray<FInterchangeStepCurve> StepCurves;` — STEP CURVE
- L45 _public member_ `double BakeFrequency = 30.0;` — This payload class part is used to get a scene node bake transform payload The translator should bake the scene node transform using the bake settings provided by the factory.
- L46 _public member_ `double RangeStartTime = 0.0;`
- L47 _public member_ `double RangeEndTime = 1.0 / BakeFrequency;`
- L48 _public member_ `TArray<FTransform> Transforms;`
- L51 _public member_ `FInterchangeAnimationPayLoadKey PayloadKey;` — PayloadKey related:
- L52 _public member_ `EInterchangeAnimationPayLoadType AdditionalSupportedType = EInterchangeAnimationPayLoadType::NONE;`
- L55 _public function_ `FAnimationPayloadData(const FString& InSceneNodeUID, const FInterchangeAnimationPayLoadKey& InPayloadKey) : SceneNodeUniqueID(InSceneNodeUID) , PayloadKey(InPayloadKey)`
- L61 _public prototype_ `void SerializeBaked(FArchive& Ar);`
- L64 _public prototype_ `void CalculateDataFor(const EInterchangeAnimationPayLoadType& ToType, const FTransform& DefaultTransform = FTransform());` — Conversions:

#### struct `UE::Interchange::FAnimationTimeDescription`  
`struct FAnimationTimeDescription`  
_L67-92_
- L69 _public member_ `double BakeFrequency;`
- L70 _public member_ `double RangeStartSecond;`
- L71 _public member_ `double RangeStopSecond;`
- L73 _public function_ `FAnimationTimeDescription() : BakeFrequency(0) , RangeStartSecond(0) , RangeStopSecond(0)`
- L80 _public function_ `FAnimationTimeDescription(double InBakeFequency, double InRangeStartSecond, double InRangeStopSecond) : BakeFrequency(InBakeFequency) , RangeStartSecond(InRangeStartSecond) , RangeStopSecond(InRangeStopSecond)`
- L88 _public function_ `uint32 GetHash() const`

#### struct `UE::Interchange::FAnimationPayloadQuery`  
`struct FAnimationPayloadQuery`  
_L94-123_
- L96 _public member_ `FString SceneNodeUniqueID;`
- L97 _public member_ `FInterchangeAnimationPayLoadKey PayloadKey;`
- L98 _public member_ `FAnimationTimeDescription TimeDescription;`
- L101 _private function_ `FAnimationPayloadQuery()`
- L106 _public function_ `FAnimationPayloadQuery(const FString& InSceneNodeUniqueID, const FInterchangeAnimationPayLoadKey& InPayloadKey, double InBakeFequency = 0, double InRangeStartSecond = 0, double InRangeStopSecond = 0) : SceneNodeUniqueID(InSceneNodeUniqueID) , PayloadKey(InPayloadKey) , TimeDescription(InBakeFequency, InRangeStartSecond, InRangeStopSecond)`
- L114 _public prototype_ `FString GetHashString() const;`
- L116 _public prototype_ `FString ToJson() const;`
- L117 _public prototype_ `void FromJson(const FString& JsonString);`
- L119 _public prototype_ `static FString ToJson(const TArray<FAnimationPayloadQuery>& Queries);`
- L120 _public prototype_ `static void FromJson(const FString& JsonString, TArray<FAnimationPayloadQuery>& Queries);`
- L122 _private member_ `mutable TOptional<FString> HashStringCache;`

#### enum `EInterchangeCurveInterpMode`  
`enum class EInterchangeCurveInterpMode : uint8`  
_L128-138_
- reflection: `UENUM()`
- desc: If using Cubic, this enum describes how the tangents should be controlled.
- L131 _public enumerator_ `Linear` — Use linear interpolation between values.
- L133 _public enumerator_ `Constant` — Use a constant value. Represents stepped values.
- L135 _public enumerator_ `Cubic` — Cubic interpolation. See TangentMode for different cubic interpolation options.
- L137 _public enumerator_ `None` — No interpolation.

#### enum `EInterchangeCurveTangentMode`  
`enum class EInterchangeCurveTangentMode : uint8`  
_L142-152_
- reflection: `UENUM()`
- desc: If using Cubic interpolation mode, this enum describes how the tangents should be controlled.
- L145 _public enumerator_ `Auto` — Automatically calculates tangents to create smooth curves between values.
- L147 _public enumerator_ `User` — User specifies the tangent as a unified tangent where the two tangents are locked to each other, presenting a consistent curve before and after.
- L149 _public enumerator_ `Break` — User specifies the tangent as two separate broken tangents on each side of the key which can allow a sharp change in evaluation before or after.
- L151 _public enumerator_ `None` — No tangents.

#### enum `EInterchangeCurveTangentWeightMode`  
`enum class EInterchangeCurveTangentWeightMode : uint8`  
_L157-167_
- reflection: `UENUM()`
- desc: Enumerates tangent weight modes.
- L160 _public enumerator_ `WeightedNone` — Don't take tangent weights into account.
- L162 _public enumerator_ `WeightedArrive` — Only take the arrival tangent weight into account for evaluation.
- L164 _public enumerator_ `WeightedLeave` — Only take the leaving tangent weight into account for evaluation.
- L166 _public enumerator_ `WeightedBoth` — Take both the arrival and leaving tangent weights into account for evaluation.

#### struct `FInterchangeCurveKey`  
`struct FInterchangeCurveKey`  
_L173-225_
- reflection: `USTRUCT()`
- desc: This struct contains only the key data, this is only used to pass animation data from translators to factories
- L179 _public member_ `EInterchangeCurveInterpMode InterpMode = EInterchangeCurveInterpMode::None;` — `UPROPERTY()` — Interpolation mode between this key and the next
- L183 _public member_ `EInterchangeCurveTangentMode TangentMode = EInterchangeCurveTangentMode::None;` — `UPROPERTY()` — Mode for tangents at this key
- L187 _public member_ `EInterchangeCurveTangentWeightMode TangentWeightMode = EInterchangeCurveTangentWeightMode::WeightedNone;` — `UPROPERTY()` — If either tangent at this key is 'weighted'
- L191 _public member_ `float Time = 0.0f;` — `UPROPERTY()` — Time at this key
- L195 _public member_ `float Value = 0.0f;` — `UPROPERTY()` — Value at this key
- L199 _public member_ `float ArriveTangent = 0.0f;` — `UPROPERTY()` — If RCIM_Cubic, the arriving tangent at this key
- L203 _public member_ `float ArriveTangentWeight = 0.0f;` — `UPROPERTY()` — If RCTWM_WeightedArrive or RCTWM_WeightedBoth, the weight of the left tangent
- L207 _public member_ `float LeaveTangent = 0.0f;` — `UPROPERTY()` — If RCIM_Cubic, the leaving tangent at this key
- L211 _public member_ `float LeaveTangentWeight = 0.0f;` — `UPROPERTY()` — If RCTWM_WeightedLeave or RCTWM_WeightedBoth, the weight of the right tangent
- L215 _public prototype_ `void ToRichCurveKey(FRichCurveKey& OutKey) const;` — Conversion to FRichCurve
- L218 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FInterchangeCurve`  
`struct FInterchangeCurve`  
_L231-250_
- reflection: `USTRUCT()`
- desc: This struct contains only the key data, this is only used to pass animation data from interchange worker process translators to factories.
- L236 _public member_ `TArray<FInterchangeCurveKey> Keys;` — `UPROPERTY()`
- L240 _public prototype_ `void ToRichCurve(FRichCurve& OutKey) const;` — Conversion to FRichCurve
- L243 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FInterchangeStepCurve`  
`struct FInterchangeStepCurve`  
_L256-281_
- reflection: `USTRUCT()`
- desc: This struct contains only the key data, this is only used to pass animation data from translators to factories.
- L261 _public member_ `TArray<float> KeyTimes;` — `UPROPERTY()`
- L262 _public member_ `TOptional<TArray<float>> FloatKeyValues;`
- L263 _public member_ `TOptional<TArray<bool>> BooleanKeyValues;`
- L264 _public member_ `TOptional<TArray<uint8>> ByteKeyValues;`
- L265 _public member_ `TOptional<TArray<int32>> IntegerKeyValues;`
- L266 _public member_ `TOptional<TArray<FString>> StringKeyValues;`
- L268 _public prototype_ `void RemoveRedundantKeys(float Threshold);`
- L270 _public prototype_ `void Serialize(FArchive& Ar);`
- L280 _private prototype_ `template<typename ValueType> void InternalRemoveRedundantKey(TArray<ValueType>& Values, TFunctionRef<bool(const ValueType& ValueA, const ValueType& ValueB)> CompareFunction);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Interchange` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L22 _prototype_ `FString HashString(const FString& String);` (scope `UE::Interchange::Private`)
- L220 _function_ `friend FArchive& operator<<(FArchive& Ar, FInterchangeCurveKey& InterchangeCurveKey)`
- L245 _function_ `friend FArchive& operator<<(FArchive& Ar, FInterchangeCurve& InterchangeCurve)`
- L272 _function_ `friend FArchive& operator<<(FArchive& Ar, FInterchangeStepCurve& InterchangeStepCurve)`

### `Plugins/Interchange/Runtime/Source/Parsers/CommonParser/Public/InterchangeCommonParserModule.h` (Public)


#### class `FInterchangeCommonParserModule`  
`class FInterchangeCommonParserModule : public IModuleInterface`  
_L11-19_
- inherits: `IModuleInterface`
- desc: This module is used to add common structure between the translators and the parsers (i.e. payload temporary structure)
- L14 _public prototype_ `static FInterchangeCommonParserModule& Get();`
- L15 _public prototype_ `static bool IsAvailable();`
- L18 _private prototype_ `virtual void StartupModule() override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define INTERCHANGECOMMONPARSER_MODULE_NAME TEXT("InterchangeCommonParser")`
