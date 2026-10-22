# Plugins / CustomizableObjectPopulation

- module root: `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulation`
- headers: 8; symbols: 186
- symbol kinds: class=13, enum=4, enumerator=24, function=7, member=68, namespace=2, prototype=59, struct=9
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, CoreUObject, InputCore, Projects, RHI, RenderCore, SlateCore
- PrivateIncludePathModuleNames: CustomizableObjectEditor
- PublicDependencyModuleNames: Core, CustomizableObject, DerivedDataCache, EditorStyle, Engine, MessageLog, Slate, UnrealEd

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulation/Internal/MuCOP/CustomizableObjectPopulationCharacteristic.h` (Internal)


#### struct `FCustomizableObjectPopulationCharacteristic`  
`struct FCustomizableObjectPopulationCharacteristic`  
_L10-24_
- reflection: `USTRUCT()`
- L18 _public member_ `FString ParameterName;` — `UPROPERTY(Category = "CustomizablePopulationClass", EditAnywhere, meta = (ToolTip = "Name of the Customizable Object Parameter that will be specified by this characteristic"))` — Name of the parameter to add contraints to
- L22 _public member_ `TArray<FCustomizableObjectPopulationConstraint> Constraints;` — `UPROPERTY(Category = "CustomizablePopulationClass", EditAnywhere, meta = (ToolTip = "Constraints applied to this characteristic"))` — List of constraints

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulation/Internal/MuCOP/CustomizableObjectPopulationConstraint.h` (Internal)


#### enum `EPopulationConstraintType`  
`enum class EPopulationConstraintType : uint8`  
_L12-23_
- reflection: `UENUM()`
- L14 _public enumerator_ `NONE`
- L15 _public enumerator_ `BOOL`
- L16 _public enumerator_ `DISCRETE`
- L17 _public enumerator_ `DISCRETE_FLOAT`
- L18 _public enumerator_ `DISCRETE_COLOR`
- L19 _public enumerator_ `TAG`
- L20 _public enumerator_ `RANGE`
- L21 _public enumerator_ `CURVE`
- L22 _public enumerator_ `CURVE_COLOR`

#### enum `ECurveColor`  
`enum class ECurveColor : uint8`  
_L27-33_
- reflection: `UENUM()`
- L29 _public enumerator_ `RED = 0`
- L30 _public enumerator_ `GREEN = 1`
- L31 _public enumerator_ `BLUE = 2`
- L32 _public enumerator_ `ALPHA = 3`

#### struct `FConstraintRanges`  
`struct FConstraintRanges`  
_L37-61_
- reflection: `USTRUCT()`
- L43 _public function_ `FConstraintRanges(): MinimumValue(0.0f), MaximumValue(0.0f), RangeWeight(1)`
- L51 _public member_ `float MinimumValue;` — `UPROPERTY(Category = "RangeConstraint", EditAnywhere, meta = (ToolTip = "Minimum value defining this range. Can't be higher than the maximum"))` — Minimum value of the range
- L55 _public member_ `float MaximumValue;` — `UPROPERTY(Category = "RangeConstraint", EditAnywhere, meta = (ToolTip = "Maximum value defining this range. Can't be lower than the minimum"))` — Maximum value of the range
- L59 _public member_ `int32 RangeWeight;` — `UPROPERTY(Category = "RangeConstraint", EditAnywhere, meta = (ToolTip = "How often this range will be used among the ranges defined by this constraint"))` — integer used to decide which range apply when multiple ranges are used for the same characteristic

#### struct `FCustomizableObjectPopulationConstraint`  
`struct FCustomizableObjectPopulationConstraint`  
_L65-125_
- reflection: `USTRUCT()`
- L71 _public function_ `FCustomizableObjectPopulationConstraint() : Type(EPopulationConstraintType::NONE), ConstraintWeight(1), TrueWeight(1), FalseWeight(1), DiscreteValue(""), DiscreteColor(FLinearColor(EForceInit::ForceInit)), Curve(nullptr), CurveColor(ECurveColor::RED)`
- L85 _public member_ `EPopulationConstraintType Type;` — `UPROPERTY(Category = "CustomizablePopulationClass", EditAnywhere)`
- L88 _public member_ `int32 ConstraintWeight;` — `UPROPERTY(Category = "CustomizablePopulationClass", EditAnywhere)` — Integer used to decide which constraint to apply when multiple constraints are used for the same characteristic
- L92 _public member_ `int32 TrueWeight;` — `UPROPERTY(Category = "BoolConstraint", EditAnywhere)` — Bool Constraint (Zero to only one of them if we want to force one option.Can't contain two zeroes)
- L95 _public member_ `int32 FalseWeight;` — `UPROPERTY(Category = "BoolConstraint", EditAnywhere)`
- L100 _public member_ `FString DiscreteValue;` — `UPROPERTY(Category = "DiscreteConstraint", EditAnywhere)` — Name of the int parameter option chosen
- L104 _public member_ `FLinearColor DiscreteColor;` — `UPROPERTY(Category = "DiscreteConstraint", EditAnywhere)` — Color chosen
- L109 _public member_ `TArray<FString> Allowlist;` — `UPROPERTY(Category = "TagConstraint", EditAnywhere)` — List of tags that force a parameter
- L113 _public member_ `TArray<FString> Blocklist;` — `UPROPERTY(Category = "TagConstraint", EditAnywhere)` — List of tags that exclude a parameter
- L117 _public member_ `TArray<FConstraintRanges> Ranges;` — `UPROPERTY(Category = "RangeConstraint", EditAnywhere)` — Ranges Constraint
- L121 _public member_ `TObjectPtr<UCurveBase> Curve;` — `UPROPERTY(Category = "CurveConstraint", EditAnywhere)` — Curve Constraint
- L124 _public member_ `ECurveColor CurveColor;` — `UPROPERTY(Category = "CurveConstraint", EditAnywhere)`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulation/Public/MuCOP/CustomizableObjectPopulation.h` (Public)


#### struct `FClassWeightPair`  
`struct FClassWeightPair`  
_L16-40_
- reflection: `USTRUCT()`
- L22 _public function_ `FClassWeightPair() : ClassWeight(1)`
- L27 _public member_ `TObjectPtr<UCustomizableObjectPopulationClass> Class = nullptr;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere, meta = (ToolTip = "Population Class that will randomply appear on Customizable Object Instances generated by this Population"))`
- L31 _public member_ `int ClassWeight;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere, meta = (ClampMin = "1", ClampMax = "100.0", ToolTip = "How often will this class appear compared to other classes. Example: One class has weight 3, the other weight 1. The final chances are 75% of the first and 25% of the last."))` — Influence of this class over all the classes of a population

#### class `UCustomizableObjectPopulation`  
`class UCustomizableObjectPopulation : public UObject`  
_L43-93_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UObject`
- L49 _public prototype_ `UCustomizableObjectPopulation();`
- L53 _public member_ `FString Name;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere, BlueprintReadOnly)` — Name of the customizable object population.
- L57 _public member_ `TArray<FClassWeightPair> ClassWeights;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere)` — List of Pupulation classes that define this population.
- L63 _public prototype_ `int32 GeneratePopulation(TArray<UCustomizableObjectInstance*>& OutInstances, int32 NumInstancesToGenerate = 1) const;` — `UFUNCTION(BlueprintPure, Category = "CustomizablePopulation")` — Create a number of instances of the target population. @return the seed that was used to create instances in this call of the GeneratePopulation. Returns -1 if there in an error with the population asset.
- L69 _public prototype_ `bool RegeneratePopulation(int32 Seed, TArray<UCustomizableObjectInstance*>& OutInstances, int32 NumInstancesToGenerate = 1) const;` — `UFUNCTION(BlueprintPure, Category = "CustomizablePopulation")` — Update the instances in the array with new parameter values for the target population. @return false if there was an error with the population asset.
- L72 _public prototype_ `bool IsValidPopulation() const;` — Allows the compilation of this population only if all its classes exist
- L74 _public prototype_ `bool HasGenerator() const;`
- L78 _public prototype_ `void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L79 _public prototype_ `bool IsCachedCookedPlatformDataLoaded(const ITargetPlatform* TargetPlatform) override;`
- L81 _public prototype_ `void CompilePopulation(UCustomizableObjectPopulationGenerator* NewGenerator = nullptr);`
- L85 _private prototype_ `void CompilePopulationInternal(UCustomizableObjectPopulation* Population);`
- L91 _private member_ `TObjectPtr<UCustomizableObjectPopulationGenerator> Generator;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L33 _function_ `friend FArchive& operator<<(FArchive& Ar, FClassWeightPair& ClassWeights)`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulation/Public/MuCOP/CustomizableObjectPopulationClass.h` (Public)


#### struct `FPopulationClassParameterOptions`  
`struct FPopulationClassParameterOptions`  
_L13-20_
- reflection: `USTRUCT()`
- L19 _public member_ `TArray<FString> Tags;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere)` — List of tags of a Parameter Option

#### struct `FPopulationClassParameter`  
`struct FPopulationClassParameter`  
_L23-36_
- reflection: `USTRUCT()`
- L31 _public member_ `TArray<FString> Tags;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere)` — List of tags of a parameter
- L35 _public member_ `TMap<FString, FPopulationClassParameterOptions> ParameterOptions;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere)` — Map of options available for a parameter can have and their tags

#### class `UCustomizableObjectPopulationClass`  
`class UCustomizableObjectPopulationClass : public UObject`  
_L39-83_
- reflection: `UCLASS()`
- inherits: `UObject`
- L45 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L49 _public member_ `FString Name;` — `UPROPERTY(Category = "CustomizablePopulationClass", EditAnywhere)` — Name of the Customizable Object Population Class
- L53 _public member_ `TObjectPtr<class UCustomizableObject> CustomizableObject;` — `UPROPERTY(Category = "CustomizablePopulationClass", EditAnywhere)` — Customizable Object that defines this class
- L61 _public member_ `TArray<FString> Allowlist;` — `UPROPERTY(Category = "CustomizablePopulationClass", EditAnywhere)` — List of parameter tags available for this class
- L65 _public member_ `TArray<FString> Blocklist;` — `UPROPERTY(Category = "CustomizablePopulationClass", EditAnywhere)` — List of parameter tags forbidden for this class
- L69 _public member_ `TArray<FCustomizableObjectPopulationCharacteristic> Characteristics;` — `UPROPERTY(Category = "CustomizablePopulationClass", EditAnywhere)` — Additional options to take into account for some parameters
- L73 _public member_ `TArray<FString> Tags;` — `UPROPERTY()` — Array with all the tags deffined for this population class
- L78 _public member_ `TObjectPtr<class UCustomizableObjectInstance> CustomizableObjectInstance = nullptr;` — Customizable Object Instance for UI purposes
- L81 _public member_ `TObjectPtr<class UCurveBase> EditorCurve;` — UCurve for UI purposes

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulation/Public/MuCOP/CustomizableObjectPopulationCustomVersion.h` (Public)


#### struct `CustomizableObjectPopulation::FCustomizableObjectPopulationCustomVersion`  
`struct FCustomizableObjectPopulationCustomVersion`  
_L12-29_
- desc: Custom serialization version for assets/classes in the CustomizableObjectPopulation and CustomizableObjectPopulationEditor modules
- L25 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L28 _private function_ `FCustomizableObjectPopulationCustomVersion()`

#### enum `CustomizableObjectPopulation::FCustomizableObjectPopulationCustomVersion::Type`  
`enum Type`  
_L14-22_
- L17 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L20 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L21 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace CustomizableObjectPopulation`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulation/Public/MuCOP/CustomizableObjectPopulationGenerator.h` (Public)


#### class `UCustomizableObjectPopulationGenerator`  
`class UCustomizableObjectPopulationGenerator : public UObject`  
_L63-90_
- reflection: `UCLASS()`
- inherits: `UObject`
- L68 _public prototype_ `UCustomizableObjectPopulationGenerator();`
- L70 _public prototype_ `int32 GeneratePopulation( TArray<UCustomizableObjectInstance*>& OutInstances, int32 NumInstancesToGenerate = 1 ) const;`
- L72 _public prototype_ `void RegeneratePopulation( int32 Seed, TArray<UCustomizableObjectInstance*>& OutInstances, int32 NumInstancesToGenerate = 1 ) const;`
- L74 _public prototype_ `void Serialize( FArchive& Ar ) override;`
- L77 _public prototype_ `void Init(TArray<UCustomizableObject*> _PopulationObjects, TSharedPtr<FCustomizableObjectPopulationGeneratorPrivate> _Private);`
- L79 _public prototype_ `bool IsCompiledForCook() const;`
- L85 _private member_ `TArray< TObjectPtr<UCustomizableObject> > PopulationObjects;` — `UPROPERTY()`
- L87 _private member_ `TSharedPtr<FCustomizableObjectPopulationGeneratorPrivate> Private;`
- L89 _private prototype_ `void Generate( int32 Seed, TArray<UCustomizableObjectInstance*>& OutPopulationInstances, int32 N ) const;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulation/Public/MuCOP/CustomizableObjectPopulationGeneratorPrivate.h` (Public)


#### class `FCustomizableObjectPopulationClassGenerator`  
`class FCustomizableObjectPopulationClassGenerator`  
_L10-35_
- L15 _public member_ `TArray<FBoolSampler> BoolSamplers;` — Bool samplers
- L18 _public member_ `TArray<FOptionSampler> IntSamplers;` — Int samplers
- L21 _public member_ `TArray<FFloatUniformSampler> UniformFloatSamplers;` — Float samplers
- L22 _public member_ `TArray<FRangesSampler> RangesSamplers;`
- L23 _public member_ `TArray<FCurveSampler> CurveSamplers;`
- L26 _public member_ `TArray<FColorCurveUniformSampler> UniformColorSamplers;` — Color samplers
- L27 _public member_ `TArray<FLinearColor> ConstantColors;`
- L30 _public member_ `TArray<FConstraintSampler> ConstraintSamplers;` — Characteristic samplers
- L32 _public prototype_ `void GenerateParameters(FRandomStream& Rand, UCustomizableObjectInstance* Instance);`

#### struct `FCustomizableObjectPopulationGeneratorPrivate`  
`struct FCustomizableObjectPopulationGeneratorPrivate`  
_L38-45_
- L40 _public member_ `FPopulationClassSampler ClassSampler;`
- L41 _public member_ `bool bPopulationCompiledForCook = false;`
- L42 _public member_ `TArray<FCustomizableObjectPopulationClassGenerator> ClassGenerators;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulation/Public/MuCOP/CustomizableObjectPopulationSamplers.h` (Public)


#### class `CustomizableObjectPopulation::FDiscreteImportanceSampler`  
`class FDiscreteImportanceSampler`  
_L14-28_
- L16 _private member_ `TArray<int32> CumulativeWeights;`
- L19 _public prototype_ `FDiscreteImportanceSampler(const TArray<int32>& Weights);`
- L20 _public prototype_ `FDiscreteImportanceSampler() = default;`
- L21 _public prototype_ `FDiscreteImportanceSampler(FDiscreteImportanceSampler&&) = default;`
- L22 _public prototype_ `FDiscreteImportanceSampler& operator=(const FDiscreteImportanceSampler&) = default;`
- L24 _public prototype_ `int32 Sample(FRandomStream& Rand) const;`
- L25 _public prototype_ `bool IsValidSampler() const;`

#### class `CustomizableObjectPopulation::FOptionSampler`  
`class FOptionSampler final : public FDiscreteImportanceSampler`  
_L30-42_
- inherits: `FDiscreteImportanceSampler`
- L32 _private member_ `TArray<FString> OptionNames;`
- L35 _public prototype_ `FOptionSampler(const TArray<int32>& OptionWeights, const TArray<FString>& OptionNames);`
- L36 _public prototype_ `FOptionSampler() = default;`
- L37 _public prototype_ `FOptionSampler(FOptionSampler&&) = default;`
- L39 _public prototype_ `const FString& GetOptionName(int32 OptionIndex) const;`

#### class `CustomizableObjectPopulation::FBoolSampler`  
`class FBoolSampler final`  
_L44-57_
- L46 _private member_ `int32 CumulativeValue = 0;`
- L47 _private member_ `int32 TippingValue = 0;`
- L50 _public prototype_ `FBoolSampler(int32 TrueWeight = 1, int32 FalseWeight = 1);`
- L51 _public prototype_ `FBoolSampler(FBoolSampler&&) = default;`
- L53 _public prototype_ `bool Sample(FRandomStream& Rand) const;`
- L54 _public prototype_ `bool IsValidSampler() const;`

#### class `CustomizableObjectPopulation::FRangesSampler`  
`class FRangesSampler final`  
_L59-73_
- L61 _private member_ `FDiscreteImportanceSampler DiscreteSampler;`
- L62 _private member_ `TArray<TTuple<float, float>> RangeValues;` — {RangeMin, RangeMax}
- L65 _public prototype_ `FRangesSampler(const TArray<int32>& RangesWeights, const TArray<TTuple<float, float>>& RangesValues);`
- L66 _public prototype_ `FRangesSampler() = default;`
- L67 _public prototype_ `FRangesSampler(FRangesSampler&&) = default;`
- L69 _public prototype_ `float Sample(FRandomStream& Rand) const;`
- L70 _public prototype_ `bool IsValidSampler() const;`

#### class `CustomizableObjectPopulation::FCurveSampler`  
`class FCurveSampler final`  
_L75-93_
- L77 _private member_ `static constexpr int32 BinAreaSampleResolution = 32;`
- L79 _private member_ `float BinWidth = 1.0f / BinAreaSampleResolution, MinT = 0.0f, MaxDefault = 0.0f;`
- L79 _private member_ `float BinWidth = 1.0f / BinAreaSampleResolution, MinT = 0.0f, MaxDefault = 0.0f;`
- L79 _private member_ `float BinWidth = 1.0f / BinAreaSampleResolution, MinT = 0.0f, MaxDefault = 0.0f;`
- L80 _private member_ `TArray<float> BinMaxHeights;`
- L81 _private member_ `TArray<float> CumulativeBinWeights;`
- L82 _private member_ `FCompressedRichCurve Curve;`
- L85 _public prototype_ `FCurveSampler(const FRichCurve& InCurve, const int32 NumBins = BinAreaSampleResolution);`
- L86 _public prototype_ `FCurveSampler() = default;`
- L87 _public prototype_ `FCurveSampler(FCurveSampler&&) = default;`
- L89 _public prototype_ `float Sample(FRandomStream& Rand) const;`
- L90 _public prototype_ `bool IsValidSampler() const;`

#### class `CustomizableObjectPopulation::FFloatUniformSampler`  
`class FFloatUniformSampler final`  
_L95-107_
- L97 _private member_ `float MinValue = 0.0f, MaxValue = 1.0f;`
- L97 _private member_ `float MinValue = 0.0f, MaxValue = 1.0f;`
- L100 _public prototype_ `FFloatUniformSampler(const float InMin = 0.0f, const float InMax = 1.0f);`
- L101 _public prototype_ `FFloatUniformSampler(FFloatUniformSampler&&) = default;`
- L103 _public prototype_ `float Sample(FRandomStream& Rand) const;`
- L104 _public prototype_ `bool IsValidSampler() const;`

#### class `CustomizableObjectPopulation::FColorCurveUniformSampler`  
`class FColorCurveUniformSampler final`  
_L109-123_
- L111 _private member_ `float MinValue = 0.0f, MaxValue = 1.0f;`
- L111 _private member_ `float MinValue = 0.0f, MaxValue = 1.0f;`
- L112 _private member_ `FCompressedRichCurve ColorCurves[4];`
- L115 _public prototype_ `FColorCurveUniformSampler(UCurveLinearColor& InCurve, const float InMin = 0.0f, const float InMax = 1.0f);`
- L116 _public prototype_ `FColorCurveUniformSampler() = default;`
- L117 _public prototype_ `FColorCurveUniformSampler(FColorCurveUniformSampler&&) = default;`
- L119 _public prototype_ `FLinearColor Sample(FRandomStream& Rand) const;`
- L120 _public prototype_ `bool IsValidSampler() const;`

#### class `CustomizableObjectPopulation::FPopulationClassSampler`  
`class FPopulationClassSampler final : public FDiscreteImportanceSampler`  
_L145-153_
- inherits: `FDiscreteImportanceSampler`
- L148 _public prototype_ `FPopulationClassSampler(const TArray<int32> & Weights);`
- L149 _public prototype_ `FPopulationClassSampler() = default;`
- L150 _public prototype_ `FPopulationClassSampler(FPopulationClassSampler&&) = default;`
- L151 _public prototype_ `FPopulationClassSampler& operator=(const FPopulationClassSampler&) = default;`

#### enum `CustomizableObjectPopulation::EPopulationSamplerType`  
`enum class EPopulationSamplerType : uint8`  
_L155-165_
- L157 _public enumerator_ `NONE`
- L158 _public enumerator_ `BOOL`
- L159 _public enumerator_ `OPTION`
- L160 _public enumerator_ `UNIFORM_FLOAT`
- L161 _public enumerator_ `RANGE`
- L162 _public enumerator_ `CURVE`
- L163 _public enumerator_ `UNIFORM_CURVE_COLOR`
- L164 _public enumerator_ `CONSTANT_COLOR`

#### struct `CustomizableObjectPopulation::FConstraintIndex`  
`struct FConstraintIndex`  
_L167-184_
- L171 _public function_ `FConstraintIndex() : SamplerIndex(-1), SamplerType(EPopulationSamplerType::NONE)`
- L175 _public function_ `FConstraintIndex(const int32 SamplerIndex, const EPopulationSamplerType SamplerType) : SamplerIndex(SamplerIndex), SamplerType(SamplerType)`
- L180 _public member_ `int32 SamplerIndex;`
- L181 _public member_ `EPopulationSamplerType SamplerType;`

#### class `CustomizableObjectPopulation::FConstraintSampler`  
`class FConstraintSampler final : public FDiscreteImportanceSampler`  
_L186-199_
- inherits: `FDiscreteImportanceSampler`
- L189 _public member_ `FString ParameterName;`
- L190 _public member_ `TArray<FConstraintIndex> Samplers;`
- L192 _public prototype_ `FConstraintSampler(const TArray<int32>& OptionWeights, const FString& ParameterName, const TArray<FConstraintIndex>& Samplers);`
- L193 _public prototype_ `FConstraintSampler() = default;`
- L194 _public prototype_ `FConstraintSampler(FConstraintSampler&&) = default;`
- L196 _public prototype_ `const FConstraintIndex& GetSamplerID(int32 SamplerIndex) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace CustomizableObjectPopulation`
