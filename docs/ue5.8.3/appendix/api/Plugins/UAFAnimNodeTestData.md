# Plugins / UAFAnimNodeTestData

- module root: `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimNodeTestData`
- headers: 2; symbols: 65
- symbol kinds: enum=1, enumerator=3, function=1, macro=1, member=48, namespace=4, struct=6, typedef=1
- PrivateDependencyModuleNames: ControlRig, Engine, RigVM, UAFAnimGraph
- PublicDependencyModuleNames: Core, CoreUObject, UAF, UAFAnimNode

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimNodeTestData/Public/UAFAnimNodeTestVars.h` (Public)


#### struct `FUAFAnimNodeNestedTestStruct`  
`struct FUAFAnimNodeNestedTestStruct`  
_L13-25_
- reflection: `USTRUCT()`
- desc: Nested struct for FBindableStruct SubProperty binding tests.
- L18 _public member_ `FVector Vec = FVector::ZeroVector;` — `UPROPERTY()`
- L21 _public member_ `FQuat Quat = FQuat::Identity;` — `UPROPERTY()`
- L24 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY()`

#### struct `FUAFAnimNodeTestVars`  
`struct FUAFAnimNodeTestVars`  
_L34-61_
- reflection: `USTRUCT()`
- desc: Minimal USTRUCT used only in UAFAnimNode LLT unit tests. Provides a set of typed properties that cover the common resolved types (bool, float, double, int32, FVector, FQuat) so that FBindableXxx runtime resolution tests can exercise variable and sub-property binding against a live FUAFAssetInstance.
- L39 _public member_ `bool bBool = false;` — `UPROPERTY(EditAnywhere, Category = "Variables")`
- L42 _public member_ `float FloatVal = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Variables")`
- L45 _public member_ `double DoubleVal = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Variables")`
- L48 _public member_ `int32 IntVal = 0;` — `UPROPERTY(EditAnywhere, Category = "Variables")`
- L51 _public member_ `FVector VectorVar = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Variables")`
- L54 _public member_ `FQuat QuatVar = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = "Variables")`
- L57 _public member_ `FTransform TransformVar = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Variables")`
- L60 _public member_ `FUAFAnimNodeNestedTestStruct NestedVar;` — `UPROPERTY(EditAnywhere, Category = "Variables")`

#### struct `FUAFAnimNodePerfVars10`  
`struct FUAFAnimNodePerfVars10`  
_L65-92_
- reflection: `USTRUCT()`
- desc: 10-property struct used by bulk-resolution performance benchmarks.
- L70 _public member_ `UPROPERTY() float f0 = 0.f;` — Float targets/sources for variable-binding benchmark
- L71 _public member_ `UPROPERTY() float f1 = 0.f;` — `UPROPERTY()` — Float targets/sources for variable-binding benchmark
- L72 _public member_ `UPROPERTY() float f2 = 0.f;` — `UPROPERTY()` — `UPROPERTY()` — Float targets/sources for variable-binding benchmark
- L73 _public member_ `UPROPERTY() float f3 = 0.f;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Float targets/sources for variable-binding benchmark
- L74 _public member_ `UPROPERTY() float f4 = 0.f;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Float targets/sources for variable-binding benchmark
- L75 _public member_ `UPROPERTY() float f5 = 0.f;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Float targets/sources for variable-binding benchmark
- L76 _public member_ `UPROPERTY() float f6 = 0.f;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Float targets/sources for variable-binding benchmark
- L77 _public member_ `UPROPERTY() float f7 = 0.f;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Float targets/sources for variable-binding benchmark
- L78 _public member_ `UPROPERTY() float f8 = 0.f;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Float targets/sources for variable-binding benchmark
- L79 _public member_ `UPROPERTY() float f9 = 0.f;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()`
- L82 _public member_ `UPROPERTY() FVector v0 = FVector::ZeroVector;` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L83 _public member_ `UPROPERTY() FVector v1 = FVector::ZeroVector;` — `UPROPERTY()` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L84 _public member_ `UPROPERTY() FVector v2 = FVector::ZeroVector;` — `UPROPERTY()` — `UPROPERTY()` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L85 _public member_ `UPROPERTY() FVector v3 = FVector::ZeroVector;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L86 _public member_ `UPROPERTY() FVector v4 = FVector::ZeroVector;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L87 _public member_ `UPROPERTY() FVector v5 = FVector::ZeroVector;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L88 _public member_ `UPROPERTY() FVector v6 = FVector::ZeroVector;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L89 _public member_ `UPROPERTY() FVector v7 = FVector::ZeroVector;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L90 _public member_ `UPROPERTY() FVector v8 = FVector::ZeroVector;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L91 _public member_ `UPROPERTY() FVector v9 = FVector::ZeroVector;` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()` — `UPROPERTY()`

#### enum `UE::UAF::EUAFAnimNodeTestEnum`  
`enum class EUAFAnimNodeTestEnum : uint8`  
_L99-104_
- reflection: `UENUM()`
- desc: Test enum for FBindableEnum exercises.
- L101 _public enumerator_ `Alpha = 0`
- L102 _public enumerator_ `Beta = 1`
- L103 _public enumerator_ `Gamma = 2`

#### struct `UE::UAF::FUAFTestAnimNodeData`  
`struct FUAFTestAnimNodeData : public FUAFAnimNodeData`  
_L107-161_
- reflection: `USTRUCT(DisplayName = "Test Anim Node", meta=(Hidden))`
- inherits: `FUAFAnimNodeData`
- L112 _public function_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override` — FUAFAnimNodeData impl
- L115 _public member_ `FBindableBool BoolVal = true;` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L118 _public member_ `FBindableFloat FloatVal = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L121 _public member_ `FBindableDouble DoubleVal = 2.0;` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L124 _public member_ `FBindableInt32 Int32Val = 3;` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L127 _public member_ `FBindableInt64 Int64Val = 4;` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L130 _public member_ `FBindableByte ByteVal = 5;` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L133 _public member_ `FBindableName NameVal = FName(TEXT("Test` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L136 _public member_ `FBindableVector VectorVal = FVector(1.0f, 2.0f, 3.0f);` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L139 _public member_ `FBindableQuat QuatVal = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L142 _public member_ `FBindableTransform TransformBindableVal = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L145 _public member_ `FBindableObject ObjectVal = FBindableObject();` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L148 _public member_ `FBindableObject ActorVal = FBindableObject(AActor::StaticClass());` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L151 _public member_ `FBindableEnum EnumVal = FBindableEnum(EUAFAnimNodeTestEnum::Beta);` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L154 _public member_ `FBindableStruct StructVal = FBindableStruct(FUAFAnimNodeTestVars{});` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L157 _public member_ `FBindableStruct TransformTrajectory = FBindableStruct(FTransformTrajectory());` — `UPROPERTY(EditAnywhere, Category = "NodeData")`
- L160 _public member_ `FBindableStruct TransformVal = FBindableStruct(FTransform());` — `UPROPERTY(EditAnywhere, Category = "NodeData")`

#### Free symbols / members of external scopes

- L94 _namespace_ `namespace UE`
- L94 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimNodeTestData/Public/UAFTestBindableTraitData.h` (Public)


#### struct `FUAFTestBindableTraitSharedData`  
`struct FUAFTestBindableTraitSharedData : public FAnimNextTraitSharedData`  
_L20-32_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- desc: Minimal test-only trait shared data with a single FBindableBool property. Used by CQTests to exercise SetPinDefaultValue round-trip on FBindable types within trait pins, verifying that the RigVM controller detects value changes through text comparison.
- L25 _public member_ `FBindableBool bTestBool = false;` — `UPROPERTY(EditAnywhere, Category = "Test")`

#### struct `UE::UAF::FTestBindableTrait`  
`struct FTestBindableTrait : FBaseTrait`  
_L41-46_
- inherits: `FBaseTrait`
- desc: Minimal test-only trait that uses FUAFTestBindableTraitSharedData. Required so that FRigDecorator_AnimNextCppDecorator can resolve the shared data struct to a registered trait during AddTrait.
- L45 _public typedef_ `using FSharedData = FUAFTestBindableTraitSharedData;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \`
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace UAF` (scope `UE`)
