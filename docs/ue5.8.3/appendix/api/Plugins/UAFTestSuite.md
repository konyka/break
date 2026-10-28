# Plugins / UAFTestSuite

- module root: `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFTestSuite`
- headers: 5; symbols: 100
- symbol kinds: class=1, enum=1, enumerator=2, function=13, macro=1, member=57, namespace=9, prototype=4, struct=10, typedef=2
- PrivateDependencyModuleNames: PythonScriptPlugin, RigVMDeveloper, UAFEditor, UAFUncookedOnly, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RigVM, UAF, UniversalObjectLocator

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFTestSuite/Private/AnimNextVariableReferenceTest.h` (Private)


#### struct `FUAFVariableReferenceTestStruct`  
`struct FUAFVariableReferenceTestStruct`  
_L9-18_
- reflection: `USTRUCT()`
- L14 _public member_ `bool Renamed_BoolVariable = false;` — `UPROPERTY()`
- L17 _public member_ `float FloatVariable = 0.f;` — `UPROPERTY()`

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFTestSuite/Private/AnimNextVariablesTest.h` (Private)


#### struct `FAnimNextParamTypeTestStruct`  
`struct FAnimNextParamTypeTestStruct`  
_L16-135_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- L21 _public member_ `bool bBool = false;` — `UPROPERTY()`
- L24 _public member_ `uint8 bBitfield0 : 1 = false;` — `UPROPERTY()`
- L27 _public member_ `uint8 bBitfield1 : 1 = false;` — `UPROPERTY()`
- L30 _public member_ `uint8 Uint8 = 0;` — `UPROPERTY()`
- L33 _public member_ `int32 Int32 = 0;` — `UPROPERTY()`
- L36 _public member_ `int64 Int64 = 0;` — `UPROPERTY()`
- L39 _public member_ `float Float = 0.0f;` — `UPROPERTY()`
- L42 _public member_ `double Double = 0.0;` — `UPROPERTY()`
- L45 _public member_ `FName Name;` — `UPROPERTY()`
- L48 _public member_ `FString String;` — `UPROPERTY()`
- L51 _public member_ `EPropertyBagContainerType Enum = EPropertyBagContainerType::None;` — `UPROPERTY()`
- L54 _public member_ `FAnimNextParamType Struct;` — `UPROPERTY()`
- L57 _public member_ `FVector Vector = FVector::ZeroVector;` — `UPROPERTY()`
- L60 _public member_ `FTransform Transform;` — `UPROPERTY()`
- L63 _public member_ `FQuat Quat = FQuat::Identity;` — `UPROPERTY()`
- L66 _public member_ `TObjectPtr<UObject> Object;` — `UPROPERTY()`
- L69 _public member_ `TObjectPtr<UClass> Class;` — `UPROPERTY()`
- L72 _public member_ `TSubclassOf<UObject> SubclassOf;` — `UPROPERTY()`
- L82 _public member_ `TArray<bool> BoolArray;` — `UPROPERTY()`
- L85 _public member_ `TArray<uint8> Uint8Array;` — `UPROPERTY()`
- L88 _public member_ `TArray<int32> Int32Array;` — `UPROPERTY()`
- L91 _public member_ `TArray<int64> Int64Array;` — `UPROPERTY()`
- L94 _public member_ `TArray<float> FloatArray;` — `UPROPERTY()`
- L97 _public member_ `TArray<double> DoubleArray;` — `UPROPERTY()`
- L100 _public member_ `TArray<FName> NameArray;` — `UPROPERTY()`
- L103 _public member_ `TArray<FString> StringArray;` — `UPROPERTY()`
- L106 _public member_ `TArray<EPropertyBagContainerType> EnumArray;` — `UPROPERTY()`
- L109 _public member_ `TArray<FAnimNextParamType> StructArray;` — `UPROPERTY()`
- L112 _public member_ `TArray<FVector> VectorArray;` — `UPROPERTY()`
- L115 _public member_ `TArray<FTransform> TransformArray;` — `UPROPERTY()`
- L118 _public member_ `TArray<FQuat> QuatArray;` — `UPROPERTY()`
- L121 _public member_ `TArray<TObjectPtr<UObject>> ObjectArray;` — `UPROPERTY()`
- L124 _public member_ `TArray<TObjectPtr<UClass>> ClassArray;` — `UPROPERTY()`
- L127 _public member_ `TArray<TSubclassOf<UObject>> SubclassOfArray;` — `UPROPERTY()`

#### struct `FAnimNextTests_TestBase`  
`struct FAnimNextTests_TestBase : public FRigVMStructMutable`  
_L138-141_
- reflection: `USTRUCT(meta=(ExecuteContext="FAnimNextExecuteContext", Hidden, DocumentationPolicy="None"))`
- inherits: `FRigVMStructMutable`

#### struct `FAnimNextTests_TestOperation`  
`struct FAnimNextTests_TestOperation : public FAnimNextTests_TestBase`  
_L144-159_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTests_TestBase`
- L148 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L152 _public member_ `int32 A = 0;` — `UPROPERTY(meta=(Input))`
- L155 _public member_ `int32 B = 0;` — `UPROPERTY(meta=(Input))`
- L158 _public member_ `int32 Result = 0;` — `UPROPERTY(meta=(Output))`

#### struct `FAnimNextTests_PrintResult`  
`struct FAnimNextTests_PrintResult : public FAnimNextTests_TestBase`  
_L162-171_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTests_TestBase`
- L166 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L170 _public member_ `int32 Result = 0;` — `UPROPERTY(meta=(Input))`

#### class `UAnimNextTestFuncLib`  
`class UAnimNextTestFuncLib : public UBlueprintFunctionLibrary`  
_L174-205_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L180 _public function_ `static UAnimNextTestFuncLib* GetObj(UUAFComponent* InObj)` — `UFUNCTION(BlueprintCallable, Category=Test)`
- L186 _public function_ `int32 GetValueB()` — `UFUNCTION(BlueprintCallable, Category=Test)`
- L192 _public function_ `static int32 GetValueC(UUAFComponent* InObj)` — `UFUNCTION(BlueprintCallable, Category=Test)`
- L198 _public member_ `int32 ValueA = 23;` — `UPROPERTY()`
- L201 _public member_ `int32 ValueB = 42;` — `UPROPERTY()`
- L204 _public member_ `int32 ValueC = 12345;` — `UPROPERTY()`

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFTestSuite/Private/UAF/ValueRuntime/IteratorTestUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L11 _function_ `template <typename IteratorType, typename ValueType, typename ProjectionType> inline bool FindWithBy(IteratorType&& It, const ValueType& Value, ProjectionType Proj)` (scope `UE::UAF::Tests`) — Tests if an iterator contains the specified value using the iterator projection functor
- L28 _function_ `template <typename IteratorType, typename ValueType, typename ProjectionType, typename PredicateType> inline bool FindWithByPredicate(IteratorType&& It, const ValueType& Value, ProjectionType Proj, PredicateType Predicate)` (scope `UE::UAF::Tests`) — Tests if an iterator contains the specified value using the iterator projection functor
- L45 _function_ `template <typename IteratorType> inline int32 IteratorSize(IteratorType&& It)` (scope `UE::UAF::Tests`) — Returns the size of the iterator
- L60 _function_ `template <typename IteratorType, typename ProjectionType, typename PredicateType> inline bool IteratorSortedByPredicate(IteratorType&& It, ProjectionType Proj, PredicateType Predicate)` (scope `UE::UAF::Tests`) — Returns whether the iterator is sorted or not

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFTestSuite/Private/UAF/ValueRuntime/Transformers/TransformerTestUtil.h` (Private)


#### struct `UE::UAF::Tests::FTransformerUnaryTest`  
`template <typename AttributeType, bool SingleBuffer> struct FTransformerUnaryTest`  
_L88-190_
- desc: Util struct to perform a transformer on an attribute of a particular value and to validate its result. FTransformUnaryTests is for transformers taking a single input. The same operation is performed on a bound value and unbound value. When calling Run we assume there is a valid attribute defined in the bound maps for the test to use. The SingleBuffer template argument determines whether the transformer only takes a single value bundle as input (which only supports in-place operations) or whether the transformer can output to a second bundle (which supports in-place and out-of-place operations)
- L90 _public member_ `FName AttributeName;`
- L91 _public member_ `AttributeType Input;`
- L93 _public typedef_ `using ApplyTransformerFunctionType = std::conditional_t<SingleBuffer, TFunction<void(FValueBundleHeap& InputOutputValues)>, TFunction<void(const FValueBundleHeap& InputValues, FValueBundleHeap& OutputValues)>>;`
- L97 _public member_ `ApplyTransformerFunctionType ApplyTransformer;`
- L98 _public member_ `TFunction<TOptional<FString>(TOptional<AttributeType> Result)> IsExpectedResult;`
- L100 _public function_ `void Run(FAutomationTestBase& Test, const FAttributeNamedSetPtr& NamedSet)`
- L138 _public function_ `void ValidateResult(FAutomationTestBase& Test, const FAttributeNamedSetPtr& NamedSet, FString ErrorPrefix, const FValueBundleHeap& Result)`

#### enum `UE::UAF::Tests::EInplaceTransformationSupport`  
`enum class EInplaceTransformationSupport`  
_L192-196_
- L194 _public enumerator_ `Allow`
- L195 _public enumerator_ `Disallow`

#### struct `UE::UAF::Tests::FTransformerBinaryTest`  
`template <typename TransformerType, typename AttributeType, EInplaceTransformationSupport InplaceSupport> struct FTransformerBinaryTest`  
_L204-308_
- desc: Util struct to perform a transformer on an attribute of a particular value and to validate its result. FTransformBinaryTest is for transformers taking two inputs. The same operation is performed on a bound value and unbound value. When calling Run we assume there is a valid attribute defined in the bound maps for the test to use. The InplaceSupport template argument determines whether the transformer allows for inplace operations.
- L206 _public member_ `FName AttributeName;`
- L207 _public member_ `AttributeType InputA;`
- L208 _public member_ `AttributeType InputB;`
- L210 _public typedef_ `using ApplyTransformerFunctionType = TFunction<void(const FValueBundleHeap& InputAValues, const FValueBundleHeap& InputBValues, FValueBundleHeap& OutputValues)>;`
- L211 _public member_ `ApplyTransformerFunctionType ApplyTransformer;`
- L213 _public member_ `TFunction<TOptional<FString>(TOptional<AttributeType> Result)> IsExpectedResult;`
- L215 _public function_ `void Run(FAutomationTestBase& Test, FAttributeNamedSetPtr NamedSet)`
- L256 _public function_ `void ValidateResult(FAutomationTestBase& Test, const FAttributeNamedSetPtr& NamedSet, FString ErrorPrefix, const FValueBundleHeap& Result)`
- L315 _public member_ `float WeightB;`
- L316 _public member_ `TOptional<AttributeType> InputA;`
- L317 _public member_ `TOptional<AttributeType> InputB;`
- L320 _public function_ `void Run(FAutomationTestBase& Test, const FAttributeNamedSetPtr& NamedSetBase, const FAttributeNamedSetPtr& NamedSetLayer)`

#### struct `UE::UAF::Tests::FTransformerBinaryTest`  
`template <typename AttributeType> struct FTransformerBinaryTest<Transformers::FLayer, AttributeType, EInplaceTransformationSupport::Allow>`  
_L312-421_
- desc: Specialization for FLayer
- L206 _public member_ `FName AttributeName;`
- L207 _public member_ `AttributeType InputA;`
- L208 _public member_ `AttributeType InputB;`
- L210 _public typedef_ `using ApplyTransformerFunctionType = TFunction<void(const FValueBundleHeap& InputAValues, const FValueBundleHeap& InputBValues, FValueBundleHeap& OutputValues)>;`
- L211 _public member_ `ApplyTransformerFunctionType ApplyTransformer;`
- L213 _public member_ `TFunction<TOptional<FString>(TOptional<AttributeType> Result)> IsExpectedResult;`
- L215 _public function_ `void Run(FAutomationTestBase& Test, FAttributeNamedSetPtr NamedSet)`
- L256 _public function_ `void ValidateResult(FAutomationTestBase& Test, const FAttributeNamedSetPtr& NamedSet, FString ErrorPrefix, const FValueBundleHeap& Result)`
- L315 _public member_ `float WeightB;`
- L316 _public member_ `TOptional<AttributeType> InputA;`
- L317 _public member_ `TOptional<AttributeType> InputB;`
- L320 _public function_ `void Run(FAutomationTestBase& Test, const FAttributeNamedSetPtr& NamedSetBase, const FAttributeNamedSetPtr& NamedSetLayer)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L24 _function_ `inline TValueOrError<TNonNullPtr<UAbstractSkeletonSetBinding>, FString> BuildSetBinding(TFunction<void(TNonNullPtr<USkeleton>)> SkeletonModifier)` (scope `UE::UAF::Tests`) — Creates a new set binding for testing Optionally can provide a function to operate on the skeleton to apply any modifications if needed SetBinding will be created with the following set hierarchy: (Everything Set) \_ SetA \_ SetB \_ SetC

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFTestSuite/Public/AnimNextTest.h` (Public)


#### struct `FAnimNextTestData`  
`struct FAnimNextTestData`  
_L11-17_
- reflection: `USTRUCT()`
- desc: --- Raw type ---
- L15 _public member_ `float A = 0.f;`
- L16 _public member_ `float B = 0.f;`

#### struct `UE::UAF::Tests::FUtils`  
`struct FUtils final`  
_L22-27_
- L25 _public prototype_ `static void CleanupAfterTests();` — Clean up after tests. Clears transaction buffer, collects garbage
- L26 _public prototype_ `static class UWorld* GetWorld();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAFTESTSUITE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace Tests` (scope `UE::UAF`)
