# Plugins / RigMapper

- module root: `Plugins/Experimental/Animation/RigMapper/Source/RigMapper`
- headers: 7; symbols: 341
- symbol kinds: class=14, delegate=9, enum=4, enumerator=29, function=52, macro=5, member=78, namespace=1, prototype=124, struct=17, typedef=8
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: AnimationCore, ControlRig, Core, CoreUObject, Engine, Json

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapper/Public/AnimNode_RigMapper.h` (Public)


#### struct `FAnimNode_RigMapper`  
`struct FAnimNode_RigMapper : public FAnimNode_Base`  
_L32-127_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L37 _public prototype_ `FAnimNode_RigMapper();`
- L41 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;` — FAnimNode_Base interface
- L42 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L43 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L44 _public function_ `virtual bool HasPreUpdate() const override`
- L45 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L46 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L47 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L48 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext & Output) override;`
- L49 _public prototype_ `virtual int32 GetLODThreshold() const override;`
- L53 _public prototype_ `bool InitializeRigMapping(USkeletalMesh* TargetMesh=nullptr);` — Initialize the rig mapper(s) from the current definitions or SKM asset user data and cache the curve indices & index mappings needed for evaluation
- L56 _public prototype_ `void EvaluateRigMapping(FPoseContext& Output);` — Evaluate the new curve values using the initialized rig mappers and sets the new output pose
- L60 _public member_ `FPoseLink SourcePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)`
- L63 _public member_ `TArray<TObjectPtr<URigMapperDefinition>> Definitions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RigMapper, meta = (PinHiddenByDefault))`
- L72 _public member_ `int32 LODThreshold = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold"))` — Max LOD that this node is allowed to run For example if you have LODThreshold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L75 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))`
- L79 _private member_ `TArray<TObjectPtr<URigMapperDefinition>> LoadedDefinitions;` — The definitions that we have loaded. Cached to check against changes and reinit if need be
- L82 _private member_ `TObjectPtr<URigMapperDefinitionUserData> LoadedUserData;` — The asset user data currently used to override definitions, if any was set on the skeletal mesh
- L85 _private member_ `FRigMapperProcessor RigMapperProcessor;` — The processor to evaluate the rig mapping
- L88 _private member_ `FRigMapperProcessor::FPoseValues CachedInputValues;` — The cached input values passed to the rig mapper processor to avoid reallocations
- L91 _private member_ `FRigMapperProcessor::FPoseValues CachedOutputValues;` — The cached output values passed to the rig mapper processor to avoid reallocations
- L121 _private typedef_ `using FInputCurveMappings = UE::Anim::TNamedValueArray<FDefaultAllocator, FRigMapperCurveMapping>;` — Input curve mapping for bulk get of the linked pose curve values
- L122 _private member_ `FInputCurveMappings InputCurveMappings;`
- L125 _private typedef_ `using FOutputCurveMappings = UE::Anim::TNamedValueArray<FDefaultAllocator, FRigMapperOutputCurveMapping>;` — Output curve mapping for the bulk get of the linked pose curve values
- L126 _private member_ `FOutputCurveMappings OutputCurveMappings;`

#### struct `FAnimNode_RigMapper::FRigMapperCurveMapping`  
`struct FRigMapperCurveMapping`  
_L94-105_
- desc: Base curve mapping for bulk get/set of the linked pose curves
- L96 _public prototype_ `FRigMapperCurveMapping() = default;`
- L98 _public function_ `FRigMapperCurveMapping(FName InName, int32 InCurveIndex) : Name(InName) , CurveIndex(InCurveIndex)`
- L103 _public member_ `FName Name = NAME_None;`
- L104 _public member_ `int32 CurveIndex = INDEX_NONE;`

#### struct `FAnimNode_RigMapper::FRigMapperOutputCurveMapping`  
`struct FRigMapperOutputCurveMapping : FRigMapperCurveMapping`  
_L108-118_
- inherits: `FRigMapperCurveMapping`
- desc: Curve mapping for bulk set of the linked pose curves with a mapping to the matching input to allow lerping with the current curve value
- L110 _public prototype_ `FRigMapperOutputCurveMapping() = default;`
- L112 _public function_ `FRigMapperOutputCurveMapping(FName InName, int32 InOutputCurveIndex, int32 InInputCurveIndex) : FRigMapperCurveMapping(InName, InOutputCurveIndex) , InputCurveIndex(InInputCurveIndex)`
- L117 _public member_ `int32 InputCurveIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGMAPPER_API`
- L21 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Evaluate Rig Mapper Node"), STAT_RigMapperEvaluateNode, STATGROUP_Ri`
- L22 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Evaluate Rig Mapping"), STAT_RigMapperEvaluateRigs, STATGROUP_RigMap`
- L23 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Initialize Rig Mapping"), STAT_RigMapperInitialize, STATGROUP_RigM`
- L24 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Rig Mapper Set Pose Curves"), STAT_RigMapperSetCurves, STATGROUP_`
- L26 _typedef_ `using FRigMapperIndexMap = TArray<int32>;`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapper/Public/RigMapper.h` (Public)


#### struct `FacialRigMapping::FNodeCollection`  
`struct FNodeCollection`  
_L26-33_
- L28 _public member_ `TArray<FInputNode> InputNodes;`
- L29 _public member_ `TArray<FEvalNodeWeightedSum> WeightedSumNodes;`
- L30 _public member_ `TArray<FEvalNodePiecewiseLinear> PiecewiseLinearNodes;`
- L31 _public member_ `TArray<FEvalNodeMultiply> MultiplyNodes;`
- L32 _public member_ `TArray<FEvalNodeMathOp> MathOpNodes;`

#### enum `FacialRigMapping::ENodeType`  
`enum class ENodeType : uint8`  
_L35-43_
- L37 _public enumerator_ `None`
- L38 _public enumerator_ `Input`
- L39 _public enumerator_ `WeightedSum`
- L40 _public enumerator_ `PiecewiseLinear`
- L41 _public enumerator_ `Multiply`
- L42 _public enumerator_ `MathOp`

#### class `FacialRigMapping::FNodePtr`  
`class FNodePtr`  
_L48-79_
- desc: Lighweight pointer/proxy to a node in the FNodeCollection.
- L51 _public prototype_ `FNodePtr() = default;`
- L52 _public prototype_ `FNodePtr(ENodeType InNodeType, int32 InDataIndex);`
- L54 _public prototype_ `bool TryGetValue(const FNodeCollection& NodeCollection, double& OutValue) const;`
- L55 _public prototype_ `double GetValue(const FNodeCollection& NodeCollection) const;`
- L56 _public prototype_ `void SetDirect(FNodeCollection& NodeCollection, double Value);`
- L57 _public prototype_ `void Reset(FNodeCollection& NodeCollection);`
- L59 _public function_ `bool IsValid() const`
- L64 _public prototype_ `bool IsInitialized(const FNodeCollection& NodeCollection) const;`
- L77 _private member_ `int32 DataIndex = INDEX_NONE;`
- L78 _private member_ `ENodeType NodeType = ENodeType::None;`

#### class `FacialRigMapping::FRigMapper`  
`class FRigMapper`  
_L84-112_
- desc: Rig Mapper node representation loaded from URigMapperDefinition
- L87 _public prototype_ `bool LoadDefinition(const URigMapperDefinition* Definition);`
- L88 _public prototype_ `bool SetDirectValue(int32 Index, double Value);`
- L89 _public prototype_ `bool SetDirectValue(const FName& InputName, double Value);`
- L90 _public prototype_ `void Reset();`
- L91 _public prototype_ `bool IsValid() const;`
- L93 _public prototype_ `TMap<FName,double> GetOutputValues(bool bSkipUnset = false) const;`
- L94 _public prototype_ `const TArray<FName>& GetOutputNames() const;`
- L95 _public prototype_ `void GetOutputValuesInOrder(TArray<double>& OutValues) const;`
- L96 _public prototype_ `void GetOptionalOutputValuesInOrder(TArray<TOptional<double>>& OutValues) const;`
- L97 _public prototype_ `void GetOptionalFloatOutputValuesInOrder(TArray<TOptional<float>>& OutValues) const;`
- L99 _public prototype_ `void SetDirty();`
- L101 _public prototype_ `const TArray<FName>& GetInputNames() const;`
- L104 _private member_ `TMap<FName, FNodePtr> Nodes;`
- L105 _private member_ `FNodeCollection NodeCollection;`
- L107 _private member_ `TArray<FNodePtr> OutputNodes;`
- L108 _private member_ `TArray<FName> OutputNames;`
- L110 _private member_ `TArray<FNodePtr> InputNodes;`
- L111 _private member_ `TArray<FName> InputNames;`

#### class `FacialRigMapping::FInputNode`  
`class FInputNode`  
_L115-140_
- L118 _public function_ `bool TryGetValue(const FNodeCollection& NodeCollection, double& OutValue) const`
- L128 _public function_ `void SetDirect(double Value)`
- L133 _public function_ `void Reset()`
- L139 _protected member_ `mutable TOptional<double> CachedValue;`

#### class `FacialRigMapping::TEvalNode`  
`template<typename DerivedNode> class TEvalNode`  
_L143-187_
- L146 _public function_ `bool TryGetValue(const FNodeCollection& NodeCollection, double& OutValue) const`
- L169 _public function_ `bool IsInitialized() const`
- L174 _public function_ `void SetDirect(double Value)`
- L179 _public function_ `void Reset()`
- L185 _protected member_ `mutable TOptional<double> CachedValue;`
- L186 _protected member_ `bool bInitialized = false;`

#### class `FacialRigMapping::FEvalNodeWeightedSum`  
`class FEvalNodeWeightedSum : public TEvalNode<FEvalNodeWeightedSum>`  
_L189-198_
- inherits: `TEvalNode<FEvalNodeWeightedSum>`
- L192 _public prototype_ `void Initialize(const FRigMapperWsFeature& FeatureDefinition, const TMap<FName, FNodePtr>& Nodes);`
- L193 _public prototype_ `bool Evaluate(const FNodeCollection& NodeCollection, double& OutValue) const;`
- L196 _private member_ `TArray<TPair<FNodePtr, double>> WeightedLinkedInputs;`
- L197 _private member_ `TRange<double> Range;`

#### class `FacialRigMapping::FEvalNodePiecewiseLinear`  
`class FEvalNodePiecewiseLinear : public TEvalNode<FEvalNodePiecewiseLinear>`  
_L200-212_
- inherits: `TEvalNode<FEvalNodePiecewiseLinear>`
- L203 _public prototype_ `void Initialize(const FRigMapperSdkFeature& FeatureDefinition, const TMap<FName, FNodePtr>& Nodes);`
- L204 _public prototype_ `bool Evaluate(const FNodeCollection& NodeCollection, double& OutValue) const;`
- L206 _public prototype_ `static bool Evaluate_Static(const double InputValue, TConstArrayView<TPair<double, double>> Keys, double& OutValue);`
- L209 _private member_ `FNodePtr LinkedInput;`
- L211 _private member_ `TArray<TPair<double, double>, TInlineAllocator<2>> Keys;` — 95% only have 2 elements in this array.

#### class `FacialRigMapping::FEvalNodeMultiply`  
`class FEvalNodeMultiply : public TEvalNode<FEvalNodeMultiply>`  
_L214-222_
- inherits: `TEvalNode<FEvalNodeMultiply>`
- L217 _public prototype_ `void Initialize(const FRigMapperMultiplyFeature& FeatureDefinition, const TMap<FName, FNodePtr>& Nodes);`
- L218 _public prototype_ `bool Evaluate(const FNodeCollection& NodeCollection, double& OutValue) const;`
- L221 _private member_ `TArray<FNodePtr, TInlineAllocator<2>> LinkedInputs;`

#### class `FacialRigMapping::FEvalNodeMathOp`  
`class FEvalNodeMathOp : public TEvalNode<FEvalNodeMathOp>`  
_L224-239_
- inherits: `TEvalNode<FEvalNodeMathOp>`
- L227 _public prototype_ `void Initialize(const FRigMapperMathFeature& FeatureDefinition, const TMap<FName, FNodePtr>& Nodes);`
- L228 _public prototype_ `bool Evaluate(const FNodeCollection& NodeCollection, double& OutValue) const;`
- L237 _private member_ `ERigMapperMathOperation Operation;`
- L238 _private member_ `TArray<FMathInput, TInlineAllocator<3>> LinkedInputs;`

#### struct `FacialRigMapping::FEvalNodeMathOp::FMathInput`  
`struct FMathInput`  
_L231-235_
- L233 _public member_ `FNodePtr Node;` — valid if connected to another node
- L234 _public member_ `double ConstantValue = 0.0;` — used if Node name is empty, meaning constant value is set

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API RIGMAPPER_API`
- L16 _namespace_ `namespace FacialRigMapping`
- L66 _function_ `friend bool operator==(const FNodePtr& Lhs, const FNodePtr& Rhs)` (scope `FacialRigMapping`)
- L71 _function_ `friend uint32 GetTypeHash(const FNodePtr& Node)` (scope `FacialRigMapping`)

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapper/Public/RigMapperDefinition.h` (Public)


#### enum `ERigMapperFeatureType`  
`enum class ERigMapperFeatureType : uint8`  
_L20-30_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `Input`
- L23 _public enumerator_ `WeightedSum`
- L24 _public enumerator_ `SDK`
- L25 _public enumerator_ `Multiply`
- L26 _public enumerator_ `MathOp`
- L27 _public enumerator_ `Output`
- L28 _public enumerator_ `NullOutput`
- L29 _public enumerator_ `Invalid`

#### enum `ERigMapperMathOperation`  
`enum class ERigMapperMathOperation : uint8`  
_L33-48_
- reflection: `UENUM(BlueprintType)`
- L35 _public enumerator_ `Min`
- L36 _public enumerator_ `Max`
- L37 _public enumerator_ `Abs`
- L38 _public enumerator_ `Negate`
- L39 _public enumerator_ `Floor`
- L40 _public enumerator_ `Ceil`
- L41 _public enumerator_ `Round`
- L42 _public enumerator_ `Divide`
- L43 _public enumerator_ `Multiply`
- L44 _public enumerator_ `Sum`
- L45 _public enumerator_ `Clamp`
- L46 _public enumerator_ `Lerp`
- L47 _public enumerator_ `Average`

#### enum `ERigMapperValidationSeverity`  
`enum class ERigMapperValidationSeverity : uint8`  
_L51-55_
- reflection: `UENUM(BlueprintType)`
- L53 _public enumerator_ `Warning`
- L54 _public enumerator_ `Error`

#### struct `FRigMapperValidationMessage`  
`struct FRigMapperValidationMessage`  
_L58-71_
- reflection: `USTRUCT(BlueprintType)`
- L63 _public member_ `ERigMapperValidationSeverity Severity = ERigMapperValidationSeverity::Warning;` — `UPROPERTY(BlueprintReadOnly, Category = "Animation|Rig Mapper")`
- L66 _public member_ `FString Message;` — `UPROPERTY(BlueprintReadOnly, Category = "Animation|Rig Mapper")`
- L70 _public member_ `int32 DefinitionIndex = INDEX_NONE;` — `UPROPERTY(BlueprintReadOnly, Category = "Animation|Rig Mapper")` — Optional: which definition in the chain caused it (INDEX_NONE for single definitions)

#### struct `FRigMapperValidationContext`  
`struct FRigMapperValidationContext`  
_L74-116_
- reflection: `USTRUCT(BlueprintType)`
- L79 _public member_ `TArray<FRigMapperValidationMessage> Messages;` — `UPROPERTY(BlueprintReadOnly, Category = "Animation|Rig Mapper")`
- L81 _public function_ `void AddWarning(const FString& Message, int32 DefinitionIndex = INDEX_NONE)`
- L86 _public function_ `void AddError(const FString& Message, int32 DefinitionIndex = INDEX_NONE)`
- L91 _public function_ `int32 GetErrorCount() const`
- L101 _public function_ `int32 GetWarningCount() const`
- L111 _public function_ `bool HasErrors() const`
- L112 _public function_ `bool HasWarnings() const`
- L115 _public prototype_ `void LogAll() const;` — Flush all messages to UE_LOG

#### struct `FRigMapperFeature`  
`struct FRigMapperFeature`  
_L119-155_
- reflection: `USTRUCT(BlueprintType)`
- L124 _public typedef_ `using FBakedInput = TPair<TSharedPtr<FRigMapperFeature>, TArray<TSharedPtr<FRigMapperFeature>>>;`
- L127 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper", meta=(DisplayPriority=0))`
- L130 _public prototype_ `virtual ~FRigMapperFeature() = default;`
- L132 _public function_ `FRigMapperFeature()`
- L134 _public function_ `explicit FRigMapperFeature(const FString& InName) : Name(InName)`
- L136 _public function_ `virtual bool LoadFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject)`
- L138 _public prototype_ `virtual bool IsValid(const TArray<FString>& InputNames, bool bWarn = false, FRigMapperValidationContext* OutContext = nullptr) const;`
- L140 _public function_ `virtual ERigMapperFeatureType GetFeatureType() const`
- L142 _public function_ `virtual void GetInputs(TArray<FString>& OutInputs) const`
- L144 _public function_ `virtual bool BakeInput(URigMapperLinkedDefinitions* LinkedDefinitions, int32 DefinitionIndex, FBakedInput& OutBakedInput, FRigMapperValidationContext* OutContext = nullptr) const`
- L146 _public function_ `virtual bool ContainsInput(const FString& InInput) const`
- L148 _public function_ `bool operator==(const FRigMapperFeature& InOther) const`
- L154 _protected prototype_ `bool GetJsonArray(TSharedPtr<FJsonObject> JsonObject, TArray<TSharedPtr<FJsonValue>>& OutArray, const FString& Identifier, const FString& OwnerIdentifier="") const;`

#### struct `FRigMapperMathInput`  
`struct FRigMapperMathInput`  
_L158-174_
- reflection: `USTRUCT(BlueprintType)`
- L164 _public member_ `FString NodeName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Rig Mapper")`
- L167 _public member_ `double ConstantValue = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Rig Mapper")`
- L169 _public function_ `bool operator==(const FRigMapperMathInput& InOther) const`

#### struct `FRigMapperMathFeature`  
`struct FRigMapperMathFeature : public FRigMapperFeature`  
_L177-269_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigMapperFeature`
- L182 _public member_ `ERigMapperMathOperation Operation = ERigMapperMathOperation::Min;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Rig Mapper", meta = (DisplayPriority = 1))`
- L185 _public member_ `TArray<FRigMapperMathInput> Inputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Rig Mapper", meta = (DisplayPriority = 2))`
- L188 _public function_ `FRigMapperMathFeature()`
- L189 _public function_ `explicit FRigMapperMathFeature(const FString& InName) : FRigMapperFeature(InName)`
- L191 _public prototype_ `virtual bool LoadFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject) override;`
- L192 _public prototype_ `virtual bool IsValid(const TArray<FString>& InputNames, bool bWarn = false, FRigMapperValidationContext* OutContext = nullptr) const override;`
- L193 _public function_ `virtual ERigMapperFeatureType GetFeatureType() const override`
- L194 _public prototype_ `virtual void GetInputs(TArray<FString>& OutInputs) const override;`
- L195 _public prototype_ `virtual bool BakeInput(URigMapperLinkedDefinitions* LinkedDefinitions, int32 DefinitionIndex, FBakedInput& OutBakedInput, FRigMapperValidationContext* OutContext = nullptr) const override;`
- L196 _public prototype_ `virtual bool ContainsInput(const FString& InInput) const override;`
- L198 _public function_ `static int32 GetMinInputCount(ERigMapperMathOperation Op)`
- L223 _public function_ `static int32 GetMaxInputCount(ERigMapperMathOperation Op)`
- L248 _public function_ `bool operator==(const FRigMapperMathFeature& InOther) const`

#### struct `FRigMapperMultiplyFeature`  
`struct FRigMapperMultiplyFeature : public FRigMapperFeature`  
_L272-301_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigMapperFeature`
- L278 _public member_ `TArray<FString> Inputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper", meta=(DisplayPriority=1))`
- L281 _public function_ `FRigMapperMultiplyFeature()`
- L283 _public function_ `explicit FRigMapperMultiplyFeature(const FString& InName) : FRigMapperFeature(InName)`
- L285 _public prototype_ `virtual bool LoadFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject) override;`
- L287 _public prototype_ `virtual bool IsValid(const TArray<FString>& InputNames, bool bWarn = false, FRigMapperValidationContext* OutContext = nullptr) const override;`
- L289 _public function_ `virtual ERigMapperFeatureType GetFeatureType() const override`
- L291 _public function_ `virtual void GetInputs(TArray<FString>& OutInputs) const override`
- L293 _public prototype_ `virtual bool BakeInput(URigMapperLinkedDefinitions* LinkedDefinitions, int32 DefinitionIndex, FBakedInput& OutBakedInput, FRigMapperValidationContext* OutContext = nullptr) const override;`
- L295 _public prototype_ `virtual bool ContainsInput(const FString& InInput) const override;`
- L297 _public function_ `bool operator==(const FRigMapperMultiplyFeature& InOther) const`

#### struct `FRigMapperFeatureRange`  
`struct FRigMapperFeatureRange`  
_L304-326_
- reflection: `USTRUCT(BlueprintType)`
- L310 _public member_ `bool bHasLowerBound = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L313 _public member_ `double LowerBound = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L316 _public member_ `bool bHasUpperBound = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L319 _public member_ `double UpperBound = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L321 _public function_ `bool operator==(const FRigMapperFeatureRange& InOther) const`

#### struct `FRigMapperWsFeature`  
`struct FRigMapperWsFeature : public FRigMapperFeature`  
_L329-375_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigMapperFeature`
- L335 _public member_ `TMap<FString, double> Inputs;` — `UPROPERTY()`
- L338 _public member_ `FRigMapperFeatureRange Range;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper", meta=(DisplayPriority=1))`
- L341 _public function_ `FRigMapperWsFeature()`
- L343 _public function_ `explicit FRigMapperWsFeature(const FString& InName) : FRigMapperFeature(InName)`
- L345 _public prototype_ `virtual bool LoadFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject) override;`
- L347 _public prototype_ `virtual bool IsValid(const TArray<FString>& InputNames, bool bWarn = false, FRigMapperValidationContext* OutContext = nullptr) const override;`
- L349 _public function_ `virtual ERigMapperFeatureType GetFeatureType() const override`
- L351 _public prototype_ `virtual void GetInputs(TArray<FString>& OutInputs) const override;`
- L353 _public prototype_ `virtual bool BakeInput(URigMapperLinkedDefinitions* LinkedDefinitions, int32 DefinitionIndex, FBakedInput& OutBakedInput, FRigMapperValidationContext* OutContext = nullptr) const override;`
- L355 _public prototype_ `virtual bool ContainsInput(const FString& InInput) const override;`
- L357 _public function_ `bool operator==(const FRigMapperWsFeature& InOther) const`

#### struct `FRigMapperSdkKey`  
`struct FRigMapperSdkKey`  
_L378-393_
- reflection: `USTRUCT(BlueprintType)`
- L384 _public member_ `double In = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L387 _public member_ `double Out = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L389 _public function_ `bool operator==(const FRigMapperSdkKey& InOther) const`

#### struct `FRigMapperSdkFeature`  
`struct FRigMapperSdkFeature : public FRigMapperFeature`  
_L396-430_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigMapperFeature`
- L402 _public member_ `FString Input;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper", meta=(DisplayPriority=1))`
- L405 _public member_ `TArray<FRigMapperSdkKey> Keys;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper", meta=(DisplayPriority=1))`
- L408 _public function_ `FRigMapperSdkFeature()`
- L410 _public function_ `explicit FRigMapperSdkFeature(const FString& InName) : FRigMapperFeature(InName)`
- L412 _public prototype_ `virtual bool LoadFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject) override;`
- L414 _public prototype_ `virtual bool IsValid(const TArray<FString>& InputNames, bool bWarn = false, FRigMapperValidationContext* OutContext = nullptr) const override;`
- L416 _public function_ `virtual ERigMapperFeatureType GetFeatureType() const override`
- L418 _public function_ `virtual void GetInputs(TArray<FString>& OutInputs) const override`
- L420 _public prototype_ `virtual bool BakeInput(URigMapperLinkedDefinitions* LinkedDefinitions, int32 DefinitionIndex, FBakedInput& OutBakedInput, FRigMapperValidationContext* OutContext = nullptr) const override;`
- L422 _public function_ `virtual bool ContainsInput(const FString& InInput) const override`
- L424 _public prototype_ `static bool BakeKeys(const FRigMapperSdkFeature& InSdk, const FRigMapperSdkFeature& OutSdk, TArray<FRigMapperSdkKey>& BakedKeys);`
- L426 _public function_ `bool operator==(const FRigMapperSdkFeature& InOther) const`

#### struct `FRigMapperFeatureDefinitions`  
`struct FRigMapperFeatureDefinitions`  
_L433-464_
- reflection: `USTRUCT(BlueprintType)`
- L438 _public member_ `TArray<FRigMapperMultiplyFeature> Multiply;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L441 _public member_ `TArray<FRigMapperWsFeature> WeightedSums;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L444 _public member_ `TArray<FRigMapperSdkFeature> SDKs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L447 _public member_ `TArray<FRigMapperMathFeature> MathOps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Rig Mapper")`
- L450 _public prototype_ `bool AddFromJsonObject(const FString& FeatureName, const TSharedPtr<FJsonObject>& JsonObject);`
- L452 _public prototype_ `bool GetFeatureNames(TArray<FString>& OutFeatureNames) const;`
- L454 _public prototype_ `bool IsValid(const TArray<FString>& InputNames, bool bWarn = false, FRigMapperValidationContext* OutContext = nullptr) const;`
- L456 _public prototype_ `void Empty();`
- L458 _public prototype_ `FRigMapperFeature* Find(const FString& FeatureName, ERigMapperFeatureType& OutFeatureType);`
- L460 _public function_ `bool operator==(const FRigMapperFeatureDefinitions& InOther) const`

#### class `URigMapperDefinition`  
`class URigMapperDefinition : public UDataAsset`  
_L471-565_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- L477 _public member_ `FOnRigMapperDefinitionCreated OnRigMapperDefinitionCreated;` — Delegate to notify listeners that we have loaded definitions
- L479 _public member_ `FOnRigMapperDefinitionUpdated OnRigMapperDefinitionUpdated;` — Delegate to notify listeners that the definition is modified (features added or deleted)
- L482 _public member_ `TArray<FString> Inputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L485 _public member_ `FRigMapperFeatureDefinitions Features;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L488 _public member_ `TMap<FString, FString> Outputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L491 _public member_ `TArray<FString> NullOutputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L494 _public member_ `bool bValidated = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Rig Mapper")`
- L499 _public member_ `TObjectPtr<UEdGraph> EditorGraph;` — `UPROPERTY()` — Graph used by the definition editor.
- L504 _private member_ `FString JsonSource;` — `UPROPERTY()`
- L508 _public prototype_ `bool LoadFromJsonFile(const FFilePath& JsonFilePath);` — `UFUNCTION(BlueprintCallable, Category="Animation|Rig Mapper")`
- L511 _public prototype_ `bool LoadFromJsonString(const FString& JsonString);` — `UFUNCTION(BlueprintCallable, Category="Animation|Rig Mapper")`
- L514 _public prototype_ `bool ExportAsJsonString(FString& OutJsonString) const;` — `UFUNCTION(BlueprintCallable, Category="Animation|Rig Mapper")`
- L517 _public prototype_ `bool ExportAsJsonFile(const FFilePath& JsonFilePath) const;` — `UFUNCTION(BlueprintCallable, Category="Animation|Rig Mapper")`
- L520 _public prototype_ `bool LoadInputsFromSkeletalMesh(const TArray<FName>& InNewInputCurves);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Rig Mapper")`
- L523 _public prototype_ `bool LoadOutputsFromSkeletalMesh(const TArray<FName>& InNewOutputCurves);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Rig Mapper")`
- L526 _public prototype_ `void Empty();` — `UFUNCTION(BlueprintCallable, Category="Animation|Rig Mapper")`
- L529 _public prototype_ `bool IsDefinitionValid(bool bWarn = false, bool bForce = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Animation|Rig Mapper")`
- L530 _public prototype_ `bool IsDefinitionValid(FRigMapperValidationContext* OutContext, bool bWarn = false, bool bForce = false) const;`
- L533 _public prototype_ `bool Validate();` — `UFUNCTION(BlueprintCallable, Category="Animation|Rig Mapper")`
- L534 _public prototype_ `bool Validate(FRigMapperValidationContext* OutContext);`
- L535 _public prototype_ `void LogAll(const FRigMapperValidationContext& InContext) const;`
- L538 _public prototype_ `bool WasDefinitionValidated() const;` — `UFUNCTION(BlueprintCallable, Category = "Animation|Rig Mapper")`
- L541 _private prototype_ `bool LoadInputsFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject);`
- L542 _private prototype_ `bool LoadFeaturesFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject, TArray<FString>& FeatureNames);`
- L543 _private prototype_ `bool LoadOutputsFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject, const TArray<FString>& FeatureNames);`
- L544 _private prototype_ `bool LoadNullOutputsFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject);`
- L545 _private prototype_ `void SetDefinitionValid(bool bValid);`
- L552 _public prototype_ `virtual void InvalidateCache();` — Only clears definition from the cache.
- L553 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L557 _public prototype_ `virtual void BroadcastDefinitionModified();` — Similar to PostEditChangeProperty but for Definition editor graph wrapper changes.
- L560 _private prototype_ `virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;`

#### class `URigMapperLinkedDefinitions`  
`class URigMapperLinkedDefinitions : public UDataAsset`  
_L568-608_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- L574 _public member_ `TArray<TObjectPtr<URigMapperDefinition>> SourceDefinitions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L577 _public member_ `TObjectPtr<URigMapperDefinition> BakedDefinition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`
- L584 _public prototype_ `bool BakeDefinitions();` — `UFUNCTION(BlueprintCallable, Category="Animation|Rig Mapper")`
- L585 _public prototype_ `bool BakeDefinitions(FRigMapperValidationContext* OutContext);`
- L588 _public prototype_ `bool Validate();` — `UFUNCTION(BlueprintCallable, Category="Animation|Rig Mapper")`
- L589 _public prototype_ `bool Validate(FRigMapperValidationContext* OutContext);`
- L592 _public prototype_ `bool AreLinkedDefinitionsValid() const;` — `UFUNCTION(BlueprintCallable, Category="Animation|Rig Mapper")`
- L593 _public prototype_ `bool AreLinkedDefinitionsValid(FRigMapperValidationContext* OutContext) const;`
- L595 _public prototype_ `bool GetBakedInputRec(const FString& InputName, const int32 DefinitionIndex, FRigMapperFeature::FBakedInput& OutBakedInput, bool& bOutMissingIsNotNullOutput, FRigMapperValidationContext* OutContext);`
- L596 _public prototype_ `void LogAll(const FRigMapperValidationContext& InContext) const;`
- L599 _private prototype_ `bool AddBakedInputFeature(const TSharedPtr<FRigMapperFeature>& Feature) const;`
- L601 _private prototype_ `void AddBakedInputs(const TArray<FRigMapperFeature::FBakedInput>& BakedInputs, const TArray<int32>& BakedOutputIndices, const TArray<TPair<FString, FString>>& PairedOutputs) const;`
- L606 _private prototype_ `virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;`

#### class `URigMapperDefinitionUserData`  
`class URigMapperDefinitionUserData : public UAssetUserData`  
_L611-618_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, HideCategories = (Object))`
- inherits: `UAssetUserData`
- L617 _public member_ `TArray<TObjectPtr<URigMapperDefinition>> Definitions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Rig Mapper")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGMAPPER_API`
- L467 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRigMapperDefinitionCreated);`
- L467 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRigMapperDefinitionCreated);`
- L468 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRigMapperDefinitionUpdated);`
- L468 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRigMapperDefinitionUpdated);`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapper/Public/RigMapperLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigMapper, Log, All);`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapper/Public/RigMapperModule.h` (Public)


#### class `FRigMapperModule`  
`class FRigMapperModule : public IModuleInterface`  
_L11-18_
- inherits: `IModuleInterface`
- desc: FRigMapperModule The Runtime Module for the Generic Sequence plugin
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapper/Public/RigMapperProcessor.h` (Public)


#### struct `FRigMapperProcessor`  
`struct FRigMapperProcessor`  
_L25-73_
- reflection: `USTRUCT()`
- desc: A helper struct to gain performance when doing some batch remapping with the Rig Mapper pipeline Useful when remapping frames every tick, or numerous frames at once, or when using chained definitions... EvaluateFrame(s) methods work best if given the same set of CurveNames at every call Also provides a static utility to load rig mappers from definitions
- L29 _public typedef_ `using FPose = TMap<FString, float>;`
- L30 _public typedef_ `using FPoseValues = TArray<TOptional<float>>;`
- L31 _public typedef_ `using FSparseBakedCurves = TMap<FFrameTime, FPoseValues>;`
- L33 _public prototype_ `FRigMapperProcessor() = default;`
- L34 _public prototype_ `explicit FRigMapperProcessor(const TArray<URigMapperDefinition*>& InDefinitions);`
- L35 _public prototype_ `explicit FRigMapperProcessor(URigMapperDefinition* InDefinition);`
- L38 _public prototype_ `bool IsValid() const;` — @returns whether we have at least one rig mapper initialized, and all rig mappers are valid
- L41 _public prototype_ `const TArray<FName>& GetInputNames() const;` — @returns the input names expected by the first rig mapper
- L44 _public prototype_ `const TArray<FName>& GetOutputNames() const;` — @returns the output names given by the last rig mapper
- L47 _public prototype_ `bool EvaluateFrames(const TArray<FName>& CurveNames, const TArray<FPoseValues>& InFrameValues, TArray<FPoseValues>& OutFrameValues);` — Evaluates a set of frames all at once - retrieve and/or cache curve names using @GetOutputNames for performance
- L50 _public prototype_ `bool EvaluateFrames(const TArray<FName>& CurveNames, const TArray<FPoseValues>& InFrameValues, TArray<FName>& OutCurveNames, TArray<FPoseValues>& OutFrameValues);` — Evaluates a set of frames all at once
- L53 _public prototype_ `bool EvaluateFrames_Interp(const TArray<FName>& CurveNames, const TArray<FPoseValues>& InFrameValues, TArray<FPoseValues>& OutFrameValues, const TArray<FFrameTime>& FrameTimes);` — Evaluates a set of frames all at once, interpolating between them using the given frame times
- L56 _public prototype_ `bool EvaluateFrame(const TArray<FName>& CurveNames, const FPoseValues& InCurveValues, FPoseValues& OutCurveValues);` — Evaluates a single frame - retrieve and/or cache curve names using @GetOutputNames for performance
- L59 _public prototype_ `bool EvaluateFrame(const TArray<FName>& CurveNames, const FPoseValues& InCurveValues, TArray<FName>& OutCurveNames, FPoseValues& OutCurveValues);` — Evaluates a single frame
- L63 _private prototype_ `bool EvaluateFrame_Internal(const TArray<FName>& CurveNames, const FPoseValues& InCurveValues, FPoseValues& OutCurveValues, int32 RigIndex);` — Evaluates a single frame for a single rig mapper
- L66 _private typedef_ `using FIndexCache = TArray<int32>;`
- L69 _private member_ `TArray<FacialRigMapping::FRigMapper> RigMappers;` — The rig mappers loaded from definitions
- L72 _private member_ `TArray<FIndexCache> IndexCache;` — An index map for each rig mapper's input - if the input curve names change between two calls, it will be rebuilt

#### class `FRigMapperDefinitionsSingleton`  
`class FRigMapperDefinitionsSingleton`  
_L78-90_
- desc: A singleton class which stores a cache of FRigMappers initialized from URigMapperDefinitions, for speed
- L81 _public prototype_ `static FRigMapperDefinitionsSingleton& Get();`
- L82 _public prototype_ `bool GetRigMapper(const TObjectPtr<const URigMapperDefinition>& InDefinition, FacialRigMapping::FRigMapper& OutRigMapper);`
- L85 _public prototype_ `void ClearFromCache(const TObjectPtr<const URigMapperDefinition>& InDefinition);` — clear rig mapper from the cache if it exists
- L87 _private prototype_ `FRigMapperDefinitionsSingleton() = default;`
- L88 _private prototype_ `virtual ~FRigMapperDefinitionsSingleton() = default;`
- L89 _private member_ `TMap<FSoftObjectPath, FacialRigMapping::FRigMapper> RigMappers;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGMAPPER_API`
- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("RigMapper"), STATGROUP_RigMapper, STATCAT_A`
- L14 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Get Rig Mapper"), STAT_RigMapperGetRigMapper, STATGROUP_RigMapper, R`
- L15 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Load Definition"), STAT_RigMapperLoadDefinition, STATGROUP_RigMapper,`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapper/Public/RigMapperUtils.h` (Public)


#### class `FRigMapperUtils`  
`class FRigMapperUtils`  
_L11-23_
- L22 _public prototype_ `static FString GenerateUniqueFeatureName(const TArray<FString>& InExistingNames, FString InDesiredName, ERigMapperFeatureType InFeatureType);` — Generates a unique name given a base one and a list of existing ones, by appending a type prefix and an index suffix. @param InExistingNames	List of existing feature names including inputs or outputs, depending on the type. @param InDesiredName		The desired Name. Note, generates '{type name}:node' if desired name is empty. @param InFeatureType		Type of the feature being generated to include/replace as a prefix. @return					Returns the unique name.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API RIGMAPPER_API`
