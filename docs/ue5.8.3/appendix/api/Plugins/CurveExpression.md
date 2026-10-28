# Plugins / CurveExpression

- module root: `Plugins/Experimental/Animation/CurveExpression/Source/Runtime`
- headers: 7; symbols: 158
- symbol kinds: class=2, delegate=1, enum=6, enumerator=30, function=14, macro=5, member=39, namespace=2, prototype=40, struct=16, typedef=3
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine

### `Plugins/Experimental/Animation/CurveExpression/Source/Runtime/Private/CurveExpressionCustomVersion.h` (Private)


#### struct `FCurveExpressionCustomVersion`  
`struct FCurveExpressionCustomVersion`  
_L7-26_
- L9 _public prototype_ `FCurveExpressionCustomVersion() = delete;`
- L25 _public member_ `const static FGuid GUID;` — The GUID for this custom version number

#### enum `FCurveExpressionCustomVersion::Type`  
`enum Type`  
_L11-22_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in niagara
- L17 _public enumerator_ `SerializedExpressions` — Serialized expressions
- L18 _public enumerator_ `ExpressionDataInSharedObject`
- L20 _public enumerator_ `VersionPlusOne`
- L21 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Experimental/Animation/CurveExpression/Source/Runtime/Public/AnimNode_RemapCurves.h` (Public)


#### struct `FAnimNode_RemapCurves`  
`struct FAnimNode_RemapCurves : public FAnimNode_RemapCurvesBase`  
_L12-21_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_RemapCurvesBase`
- L18 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;` — FAnimNode_Base interface
- L20 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNode_RemapCurves> : public TStructOpsTypeTraitsBase2<FAnimNode_RemapCurves>`  
_L23-29_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNode_RemapCurves>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L26-28_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CURVEEXPRESSION_API`
- L27 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anona2d57da50103`)

### `Plugins/Experimental/Animation/CurveExpression/Source/Runtime/Public/AnimNode_RemapCurvesBase.h` (Public)


#### enum `ERemapCurvesExpressionSource`  
`enum class ERemapCurvesExpressionSource : uint8`  
_L15-20_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `ExpressionList`
- L18 _public enumerator_ `DataAsset`
- L19 _public enumerator_ `ExpressionMap`

#### struct `FAnimNode_RemapCurvesBase`  
`struct FAnimNode_RemapCurvesBase : public FAnimNode_Base`  
_L24-89_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L30 _public member_ `FPoseLink SourcePose;` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category = Links)`
- L33 _public member_ `ERemapCurvesExpressionSource ExpressionSource = ERemapCurvesExpressionSource::ExpressionList;` — `UPROPERTY(EditAnywhere, Category = Expressions)`
- L36 _public member_ `FCurveExpressionList ExpressionList;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Expressions, meta=(NeverAsPin, EditCondition="ExpressionSource==ERemapCurvesExpressionSource::ExpressionList", EditConditionHides))`
- L39 _public member_ `TObjectPtr<UCurveExpressionsDataAsset> CurveExpressionsDataAsset;` — `UPROPERTY(BlueprintReadWrite, Category = Expressions, meta=(PinShownByDefault))`
- L42 _public member_ `TMap<FName, FString> CurveExpressions;` — `UPROPERTY(BlueprintReadWrite, editfixedsize, Category = Expressions, DisplayName = "Expression Map", meta = (PinShownByDefault, EditCondition="ExpressionSource==ERemapCurvesExpressionSource::ExpressionMap", EditConditionHides))`
- L46 _public member_ `bool bExpressionsImmutable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Expressions, DisplayName = "Expression Map Does Not Change at Runtime", meta=(NeverAsPin, EditCondition="ExpressionSource==ERemapCurvesExpressionSource::ExpressionMap", EditConditionHides))` — The expression map given is immutable and will not change during runtime. Improves performance.
- L50 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base overrides
- L51 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L52 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L56 _public prototype_ `void ParseAndCacheExpressions();` — Parse and cache expressions defined in ExpressionList or CurveExpressions, depending on on use.
- L60 _public prototype_ `void VerifyExpressions( const USkeletalMeshComponent* InTargetComponent, const USkeletalMeshComponent* InSourceComponent, TFunction<void(FString)> InReportingFunc ) const;` — Call to verify the expressions. Write out any warnings to the InReportingFunc function.
- L67 _public prototype_ `bool CanVerifyExpressions() const;` — Returns true if we're able to verify expressions at all. I.e. if the expression engine has not been initialized.
- L72 _protected prototype_ `void SerializeNode(FArchive& Ar, void* InNodeThisPtr, UScriptStruct* InNodeStruct);` — Specialized serializer to serialize expression data.
- L74 _protected prototype_ `const TMap<FName, CurveExpression::Evaluator::FExpressionObject>& GetCompiledAssignments() const;`
- L75 _protected prototype_ `const TArray<FName>& GetCompiledExpressionConstants() const;`
- L77 _protected prototype_ `TMap<FName, FStringView> GetRawExpressions() const;`
- L83 _private member_ `TArray<FName> CachedConstantNames;` — `UPROPERTY()` — Serialized data.
- L85 _private member_ `mutable TSharedPtr<const FExpressionData> CachedAssetExpressionData;`
- L87 _private member_ `TMap<FName, CurveExpression::Evaluator::FExpressionObject> CachedExpressions;`
- L88 _private member_ `TOptional<int32> ExpressionMapHash;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CURVEEXPRESSION_API`

### `Plugins/Experimental/Animation/CurveExpression/Source/Runtime/Public/AnimNode_RemapCurvesFromMesh.h` (Public)


#### struct `FAnimNode_RemapCurvesFromMesh`  
`struct FAnimNode_RemapCurvesFromMesh : public FAnimNode_RemapCurvesBase`  
_L13-47_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_RemapCurvesBase`
- L20 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SourceMeshComponent;` — `UPROPERTY(BlueprintReadWrite, transient, Category=Copy, meta=(PinShownByDefault, DisplayAfter="SourcePose"))` — This is used by default if it's valid
- L24 _public member_ `bool bUseAttachedParent = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Copy, meta=(NeverAsPin))` — If SourceMeshComponent is not valid, and if this is true, it will look for attached parent as a source
- L27 _public function_ `virtual bool HasPreUpdate() const override` — FAnimNode_Base interface
- L28 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L29 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L30 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L32 _public prototype_ `bool Serialize(FArchive& Ar);`
- L35 _private prototype_ `void ReinitializeMeshComponent(USkeletalMeshComponent* InNewSkeletalMeshComponent, USkeletalMeshComponent* InTargetMeshComponent);`
- L36 _private prototype_ `void RefreshMeshComponent(USkeletalMeshComponent* InTargetMeshComponent);`
- L39 _private member_ `TWeakObjectPtr<const USkeletalMeshComponent> CurrentlyUsedSourceMeshComponent;` — this is source mesh references, so that we could compare and see if it has changed
- L40 _private member_ `TWeakObjectPtr<const USkeletalMesh> CurrentlyUsedSourceMesh;`
- L43 _private member_ `TWeakObjectPtr<const USkeletalMesh> CurrentlyUsedTargetMesh;` — target mesh
- L46 _private member_ `TMap<FName, float> SourceCurveValues;` — Transient data.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNode_RemapCurvesFromMesh> : public TStructOpsTypeTraitsBase2<FAnimNode_RemapCurvesFromMesh>`  
_L49-55_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNode_RemapCurvesFromMesh>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L52-54_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CURVEEXPRESSION_API`
- L53 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon5f2a37260103`)

### `Plugins/Experimental/Animation/CurveExpression/Source/Runtime/Public/CurveExpressionModule.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCurveExpression, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCurveExpression, Log, All);`

### `Plugins/Experimental/Animation/CurveExpression/Source/Runtime/Public/CurveExpressionsDataAsset.h` (Public)


#### struct `FCurveExpressionAssignment`  
`struct FCurveExpressionAssignment`  
_L14-20_
- L16 _public member_ `int32 LineIndex = INDEX_NONE;`
- L17 _public member_ `FName TargetName;`
- L19 _public member_ `FStringView Expression;`

#### struct `FCurveExpressionParsedAssignment`  
`struct FCurveExpressionParsedAssignment`  
_L23-29_
- L25 _public member_ `int32 LineIndex = INDEX_NONE;`
- L26 _public member_ `FName TargetName;`
- L28 _public member_ `TVariant<CurveExpression::Evaluator::FExpressionObject, CurveExpression::Evaluator::FParseError> Result;`

#### struct `FCurveExpressionList`  
`struct FCurveExpressionList`  
_L33-44_
- reflection: `USTRUCT(BlueprintType)`
- L38 _public member_ `FString AssignmentExpressions;` — `UPROPERTY(EditAnywhere, Category="Curve Expressions")`
- L40 _public prototype_ `TArray<FCurveExpressionAssignment> GetAssignments() const;`
- L43 _public prototype_ `TArray<FCurveExpressionParsedAssignment> GetParsedAssignments() const;` — Return compiled expression results

#### struct `FExpressionData`  
`struct FExpressionData`  
_L46-50_
- L48 _public member_ `TArray<FName> NamedConstants;`
- L49 _public member_ `TMap<FName, CurveExpression::Evaluator::FExpressionObject> ExpressionMap;`

#### class `UCurveExpressionsDataAsset`  
`class UCurveExpressionsDataAsset : public UDataAsset`  
_L54-82_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- L62 _public member_ `FCurveExpressionList Expressions;` — `UPROPERTY(EditAnywhere, Category="Expressions")`
- L65 _public function_ `TSharedPtr<const FExpressionData> GetCompiledExpressionData() const`
- L68 _public prototype_ `void Serialize(FArchive& Ar) override;` — UObject overrides
- L70 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L75 _private prototype_ `void CompileExpressions();`
- L79 _private member_ `TArray<FName> NamedConstants_DEPRECATED;` — `UPROPERTY()`
- L81 _private member_ `TSharedPtr<FExpressionData> ExpressionData;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CURVEEXPRESSION_API`

### `Plugins/Experimental/Animation/CurveExpression/Source/Runtime/Public/ExpressionEvaluator.h` (Public)


#### struct `CurveExpression::Evaluator::FParseLocation`  
`struct FParseLocation`  
_L16-36_
- L18 _public prototype_ `FParseLocation() = default;`
- L19 _public function_ `FParseLocation(int32 InStart, int32 InEndLocation) : Start(InStart), End(InEndLocation)`
- L23 _public function_ `FParseLocation(FStringView InParseRange, const TCHAR* InParseStart) : Start(static_cast<int32>(InParseRange.begin() - InParseStart)), End(static_cast<int32>(InParseRange.end() - InParseStart))`
- L29 _public function_ `FParseLocation Join(const FParseLocation& InLocation) const` — Merge two parse locations and return a new one
- L34 _public member_ `const int32 Start = INDEX_NONE;`
- L35 _public member_ `const int32 End = INDEX_NONE;`

#### struct `CurveExpression::Evaluator::FParseError`  
`struct FParseError`  
_L38-51_
- L40 _public prototype_ `FParseError() = default;`
- L41 _public function_ `FParseError(FString&& InMessage, FParseLocation InLocation) : Message(MoveTemp(InMessage)), Location(InLocation)`
- L47 _public member_ `const FString Message{};` — The human-readable parsing error
- L50 _public member_ `const FParseLocation Location{};` — The parse location where the error took place.

#### struct `CurveExpression::Evaluator::FExpressionObject`  
`struct FExpressionObject`  
_L53-86_
- L55 _public prototype_ `FString ToString() const;`
- L58 _public prototype_ `TSet<FName> GetUsedConstants() const;` — Returns all named constants used by this expression
- L60 _public prototype_ `void Load(FArchive& Ar);`
- L61 _public prototype_ `void Save(FArchive& Ar) const;`
- L84 _private typedef_ `using OpElement = TVariant<EOperator, FName , FFunctionRef, float>;`
- L85 _private member_ `TArray<OpElement, TInlineAllocator<8>> Expression;`

#### enum `CurveExpression::Evaluator::FExpressionObject::EOperator`  
`enum class EOperator : int32`  
_L65-75_
- L67 _public enumerator_ `Negate` — Negation operator.
- L68 _public enumerator_ `Add` — Add last two values on stack and add the result to the stack.
- L69 _public enumerator_ `Subtract` — Same but subtract
- L70 _public enumerator_ `Multiply` — Same but multiply
- L71 _public enumerator_ `Divide` — Same but divide (div-by-zero returns zero)
- L72 _public enumerator_ `Modulo` — Same but modulo (mod-by-zero returns zero)
- L73 _public enumerator_ `Power` — Raise to power
- L74 _public enumerator_ `FloorDivide` — Divide and round the result down

#### struct `CurveExpression::Evaluator::FExpressionObject::FFunctionRef`  
`struct FFunctionRef`  
_L77-81_
- L79 _public function_ `FFunctionRef(int32 InIndex) : Index(InIndex)`
- L80 _public member_ `int32 Index;`

#### class `CurveExpression::Evaluator::FEngine`  
`class FEngine`  
_L113-236_
- L118 _public prototype_ `TVariant<FExpressionObject, FParseError> Parse( FStringView InExpression, TFunction<TOptional<float>(FName InConstantName)> InConstantEvaluator = {} ) const;` — Parse an expression and either receive an error or a expression execution object that matches this evaluator.
- L127 _public prototype_ `float Execute( const FExpressionObject& InExpressionObject, TFunctionRef<TOptional<float>(FName InConstantName)> InConstantEvaluator ) const;` — Executes the given expression object. \param InExpressionObject The parsed expression object to evaluate. \param InConstantEvaluator A function that returns the value of a given constant, if it's known, or none otherwise.
- L135 _public prototype_ `TOptional<float> Evaluate( FStringView InExpression, TFunctionRef<TOptional<float>(FName InConstantName)> InConstantEvaluator ) const;` — Evaluate an expression directly and returns the result. If the expression is incorrectly formed, then the optional return value holds nothing.
- L142 _public prototype_ `TOptional<FParseError> Verify( FStringView InExpression, TFunction<TOptional<float>(FName InConstantName)> InConstantEvaluator = {} ) const;` — Verify an expression. Does not check for variable validity, only that the expression can be evaluated
- L164 _private typedef_ `using FToken = TVariant<EOperatorToken, FName, float>;`
- L200 _private prototype_ `static FTokenParseResult ParseFloat( FStringView& InOutParseRange, FStringView InExpression );` — Parse a floating point value and return the result (or error). Same semantics apply as with ParseToken.
- L208 _private prototype_ `static FTokenParseResult ParseIdentifier( FStringView& InOutParseRange, FStringView InExpression );` — Parse a constant reference and return the result (or error). Same semantics apply as with ParseToken.
- L218 _private prototype_ `static FTokenParseResult ParseToken( FStringView& InOutParseRange, FStringView InExpression );` — Parse a single token from the beginning of the range, returning either the token or an error, if one was encountered. If the token was successfully parsed, then the given string view range gets updated with the new starting point at the end of the token just parsed
- L224 _private prototype_ `static FString TokenToString( const FToken& InToken );` — Helper function to get a text version of a token.
- L230 _private typedef_ `using FunctionType = TFunction<float(TArrayView<const float>)>;`

#### enum `CurveExpression::Evaluator::FEngine::EOperatorToken`  
`enum class EOperatorToken`  
_L148-163_
- L150 _public enumerator_ `Negate` — Placeholder for when constructing the op stack. Gets converted to (0 - V)
- L151 _public enumerator_ `Add` — '+'
- L152 _public enumerator_ `Subtract` — '-'
- L153 _public enumerator_ `Multiply` — '*'
- L154 _public enumerator_ `Divide` — '/'
- L155 _public enumerator_ `Modulo` — '%'
- L156 _public enumerator_ `Power` — '**'
- L157 _public enumerator_ `FloorDivide` — '//'
- L158 _public enumerator_ `ParenOpen` — '('
- L159 _public enumerator_ `ParenClose` — ')'
- L160 _public enumerator_ `Comma` — ','
- L162 _public enumerator_ `Max` — Must be last

#### struct `CurveExpression::Evaluator::FEngine::FTokenParseResult`  
`struct FTokenParseResult`  
_L166-195_
- L168 _public prototype_ `FTokenParseResult() = default;`
- L170 _public function_ `FTokenParseResult(FToken&& InToken, FStringView InTokenRange, const TCHAR* InExpression) : Result(TInPlaceType<FToken>(), MoveTemp(InToken)), Location(InTokenRange, InExpression)`
- L175 _public function_ `FTokenParseResult(FString&& InError, FStringView InTokenRange, const TCHAR* InExpression) : Result(TInPlaceType<FString>(), MoveTemp(InError)), Location(InTokenRange, InExpression)`
- L180 _public function_ `bool IsError() const`
- L181 _public function_ `bool IsToken() const`
- L183 _public function_ `const FToken& GetToken() const`
- L188 _public function_ `FParseError GetParseError()`
- L193 _public member_ `TVariant<FString, FToken> Result;`
- L194 _public member_ `FParseLocation Location{};`

#### struct `CurveExpression::Evaluator::FEngine::FFunctionInfo`  
`struct FFunctionInfo`  
_L231-235_
- L233 _public member_ `int32 ArgumentCount;`
- L234 _public member_ `FunctionType FunctionPtr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CURVEEXPRESSION_API`
- L13 _namespace_ `namespace CurveExpression`
- L13 _namespace_ `namespace Evaluator` (scope `CurveExpression`)
- L241 _function_ `static FArchive& operator<<(FArchive& Ar, CurveExpression::Evaluator::FExpressionObject& InObject)`
