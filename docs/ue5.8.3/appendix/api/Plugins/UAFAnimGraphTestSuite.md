# Plugins / UAFAnimGraphTestSuite

- module root: `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimGraphTestSuite`
- headers: 8; symbols: 100
- symbol kinds: class=1, enum=1, enumerator=1, function=2, macro=2, member=55, namespace=2, prototype=15, struct=21
- PrivateDependencyModuleNames: CQTest, Core, CoreUObject, Engine, PythonScriptPlugin, RigVM, RigVMDeveloper, UAF, UAFAnimGraph, UAFAnimGraphEditor, UAFAnimGraphUncookedOnly, UAFEditor, UAFTestSuite, UAFUncookedOnly, UnrealEd

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimGraphTestSuite/Private/AnimNextAnimGraphTraitEventTest.h` (Private)


#### struct `FTraitAnimGraphTest_EventA`  
`struct FTraitAnimGraphTest_EventA : public FAnimNextTraitEvent`  
_L10-17_
- inherits: `FAnimNextTraitEvent`
- L12 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FTraitAnimGraphTest_EventA, FAnimNextTraitEvent) bool bTestFlag = false;`
- L16 _public member_ `TArray<UE::UAF::FTraitUID> VisitedTraits;`

#### struct `FTraitAnimGraphTest_EventB`  
`struct FTraitAnimGraphTest_EventB : public FAnimNextTraitEvent`  
_L19-29_
- inherits: `FAnimNextTraitEvent`
- L21 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FTraitAnimGraphTest_EventB, FAnimNextTraitEvent) bool bTestFlag0 = false;`
- L24 _public member_ `bool bTestFlag1 = false;`
- L26 _public member_ `TArray<UE::UAF::FTraitUID> VisitedTraits;`
- L28 _public member_ `FAnimNextTraitEventPtr ChildEvent;`

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimGraphTestSuite/Private/AnimNextAnimGraphTraitGraphTest.h` (Private)


#### struct `FTestTraitSharedData`  
`struct FTestTraitSharedData : public FAnimNextTraitSharedData`  
_L14-55_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L19 _public member_ `int32 UpdateCount = 0;` — `UPROPERTY(meta = (Input, Inline))`
- L22 _public member_ `int32 EvaluateCount = 0;` — `UPROPERTY(meta = (Input, Inline))`
- L25 _public member_ `int32 SomeInt32 = 3;` — `UPROPERTY(meta = (Input, Inline))`
- L28 _public member_ `float SomeFloat = 34.0f;` — `UPROPERTY(meta = (Input, Inline))`
- L31 _public member_ `int32 SomeLatentInt32 = 5;` — `UPROPERTY(meta = (Input))` — MathAdd with constants, latent
- L34 _public member_ `int32 SomeOtherLatentInt32 = 7;` — `UPROPERTY(meta = (Input))` — GetParameter, latent
- L37 _public member_ `bool SomeOutOfOrderLatentBool = false;` — `UPROPERTY(meta = (Input))` — GetParameter, latent
- L40 _public member_ `FVector SomeLatentVector = FVector::OneVector;` — `UPROPERTY(meta = (Input))` — GetParameter, latent
- L43 _public member_ `float SomeLatentFloat = 34.0f;` — `UPROPERTY(meta = (Input))` — Inline value, not latent

#### struct `FTestDerivedVector`  
`struct FTestDerivedVector : public FVector`  
_L58-68_
- reflection: `USTRUCT()`
- inherits: `FVector`
- L62 _public function_ `FTestDerivedVector() : FVector(FVector::OneVector)`
- L67 _public member_ `int32 W = 1;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L45 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \`

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimGraphTestSuite/Private/AnimNextAnimGraphTraitInterfacesTest.h` (Private)


#### struct `FTraitWithOneChildSharedData`  
`struct FTraitWithOneChildSharedData : public FAnimNextTraitSharedData`  
_L13-19_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L18 _public member_ `FAnimNextTraitHandle Child;` — `UPROPERTY()`

#### struct `FTraitWithChildrenSharedData`  
`struct FTraitWithChildrenSharedData : public FAnimNextTraitSharedData`  
_L22-28_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L27 _public member_ `FAnimNextTraitHandle Children[2];` — `UPROPERTY()`

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimGraphTestSuite/Private/AnimNextInlineSubGraphTraitTest.h` (Private)


#### struct `FInlineSubGraphTest_LeafTraitSharedData`  
`struct FInlineSubGraphTest_LeafTraitSharedData : public FAnimNextTraitSharedData`  
_L10-16_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L15 _public member_ `int32 Value = 0;` — `UPROPERTY()`

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimGraphTestSuite/Private/AnimNextRuntimeTest.h` (Private)


#### struct `UE::UAF::FScopedClearNodeTemplateRegistry`  
`struct FScopedClearNodeTemplateRegistry final`  
_L72-86_
- desc: Captures the node template registry and restores its state when we go out of scope
- L76 _public prototype_ `FScopedClearNodeTemplateRegistry();`
- L77 _public prototype_ `~FScopedClearNodeTemplateRegistry();`
- L81 _public member_ `int32 OldTemplateBufferSize = 0;` — The size of the TemplateBuffer in the node registry when the scope began We'll restore it to that size (it is append only) when the scope ends
- L85 _public member_ `TMap<uint32, FNodeTemplateRegistryHandle> OldTemplateUIDToHandleMap;` — The TemplateUIDToHandleMap in the node registry when the scope began We'll restore it to this one when the scope ends

#### struct `UE::UAF::FScopedNewNodeTemplateRegistry`  
`struct FScopedNewNodeTemplateRegistry final`  
_L90-102_
- desc: Creates a temporary empty node template registry instance and swaps it for the current one until the end of the scope Should only be used when testing the node registry itself
- L94 _public prototype_ `FScopedNewNodeTemplateRegistry();`
- L95 _public prototype_ `~FScopedNewNodeTemplateRegistry();`
- L98 _public member_ `FNodeTemplateRegistry TmpRegistry;` — The new temporary node registry instance we'll set as the global one
- L101 _public member_ `FNodeTemplateRegistry* OriginalRegistry = nullptr;` — The old node registry instance we'll restore once we go out of scope

#### struct `UE::UAF::FTestUtils`  
`struct FTestUtils final`  
_L104-109_
- L108 _public prototype_ `static bool LoadFromArchiveBuffer(UUAFAnimGraph& AnimationGraph, TArray<FNodeHandle>& NodeHandles, const TArray<uint8>& SharedDataArchiveBuffer);` — Loads the module data from the provided archive buffer and returns true on success, false otherwise On success, we resolve every node handle provided as argument

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L24 _function_ `template<class TraitSharedDataType, typename PropertyType> static FString ToString(const FString& PropertyName, PropertyType PropertyValue)` (scope `UE::UAF`) — Converts a property value into its string representation using UE reflection

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimGraphTestSuite/Private/AnimNextTraitBaseTest.h` (Private)


#### struct `FTraitA_BaseSharedData`  
`struct FTraitA_BaseSharedData : public FAnimNextTraitSharedData`  
_L12-20_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L17 _public member_ `uint32 TraitUID;` — `UPROPERTY(meta = (Inline))`
- L19 _public prototype_ `FTraitA_BaseSharedData();`

#### struct `FTraitAB_AddSharedData`  
`struct FTraitAB_AddSharedData : public FAnimNextTraitSharedData`  
_L23-31_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L28 _public member_ `uint32 TraitUID;` — `UPROPERTY(meta = (Inline))`
- L30 _public prototype_ `FTraitAB_AddSharedData();`

#### struct `FTraitAC_AddSharedData`  
`struct FTraitAC_AddSharedData : public FAnimNextTraitSharedData`  
_L34-42_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L39 _public member_ `uint32 TraitUID;` — `UPROPERTY(meta = (Inline))`
- L41 _public prototype_ `FTraitAC_AddSharedData();`

#### struct `FTraitSerialization_BaseSharedData`  
`struct FTraitSerialization_BaseSharedData : public FAnimNextTraitSharedData`  
_L45-72_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L50 _public member_ `int32 Integer = 0;` — `UPROPERTY(meta = (Inline))`
- L53 _public member_ `int32 IntegerArray[4] = { 0, 0, 0, 0 };` — `UPROPERTY(meta = (Inline))`
- L56 _public member_ `TArray<int32> IntegerTArray;` — `UPROPERTY(meta = (Inline))`
- L59 _public member_ `FVector Vector = FVector::ZeroVector;` — `UPROPERTY(meta = (Inline))`
- L62 _public member_ `FVector VectorArray[2] = { FVector::ZeroVector, FVector::ZeroVector };` — `UPROPERTY(meta = (Inline))`
- L65 _public member_ `TArray<FVector> VectorTArray;` — `UPROPERTY(meta = (Inline))`
- L68 _public member_ `FString String;` — `UPROPERTY(meta = (Inline))`
- L71 _public member_ `FName Name;` — `UPROPERTY(meta = (Inline))`

#### struct `FTraitSerialization_AddSharedData`  
`struct FTraitSerialization_AddSharedData : public FAnimNextTraitSharedData`  
_L75-102_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L80 _public member_ `int32 Integer = 0;` — `UPROPERTY(meta = (Inline))`
- L83 _public member_ `int32 IntegerArray[4] = { 0, 0, 0, 0 };` — `UPROPERTY(meta = (Inline))`
- L86 _public member_ `TArray<int32> IntegerTArray;` — `UPROPERTY(meta = (Inline))`
- L89 _public member_ `FVector Vector = FVector::ZeroVector;` — `UPROPERTY(meta = (Inline))`
- L92 _public member_ `FVector VectorArray[2] = { FVector::ZeroVector, FVector::ZeroVector };` — `UPROPERTY(meta = (Inline))`
- L95 _public member_ `TArray<FVector> VectorTArray;` — `UPROPERTY(meta = (Inline))`
- L98 _public member_ `FString String;` — `UPROPERTY(meta = (Inline))`
- L101 _public member_ `FName Name;` — `UPROPERTY(meta = (Inline))`

#### struct `FTraitNativeSerialization_AddSharedData`  
`struct FTraitNativeSerialization_AddSharedData : public FAnimNextTraitSharedData`  
_L105-136_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L110 _public member_ `int32 Integer = 0;` — `UPROPERTY(meta = (Inline))`
- L113 _public member_ `int32 IntegerArray[4] = { 0, 0, 0, 0 };` — `UPROPERTY(meta = (Inline))`
- L116 _public member_ `TArray<int32> IntegerTArray;` — `UPROPERTY(meta = (Inline))`
- L119 _public member_ `FVector Vector = FVector::ZeroVector;` — `UPROPERTY(meta = (Inline))`
- L122 _public member_ `FVector VectorArray[2] = { FVector::ZeroVector, FVector::ZeroVector };` — `UPROPERTY(meta = (Inline))`
- L125 _public member_ `TArray<FVector> VectorTArray;` — `UPROPERTY(meta = (Inline))`
- L128 _public member_ `FString String;` — `UPROPERTY(meta = (Inline))`
- L131 _public member_ `FName Name;` — `UPROPERTY(meta = (Inline))`
- L133 _public member_ `bool bSerializeCalled = false;`
- L135 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTraitNativeSerialization_AddSharedData> : public TStructOpsTypeTraitsBase2<FTraitNativeSerialization_AddSharedData>`  
_L139-145_
- inherits: `TStructOpsTypeTraitsBase2<FTraitNativeSerialization_AddSharedData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L142-144_

#### Free symbols / members of external scopes

- L143 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonbb11d3460103`)

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimGraphTestSuite/Private/AnimNextTraitEventTest.h` (Private)


#### struct `FTraitCoreTest_EventA`  
`struct FTraitCoreTest_EventA : public FAnimNextTraitEvent`  
_L10-17_
- inherits: `FAnimNextTraitEvent`
- L12 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FTraitCoreTest_EventA, FAnimNextTraitEvent) bool bAlwaysForwardToBase = true;`
- L16 _public member_ `TArray<UE::UAF::FTraitUID> VisitedTraits;`

#### struct `FTraitCoreTest_EventB`  
`struct FTraitCoreTest_EventB : public FAnimNextTraitEvent`  
_L19-24_
- inherits: `FAnimNextTraitEvent`
- L21 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FTraitCoreTest_EventB, FAnimNextTraitEvent) TArray<UE::UAF::FTraitUID> VisitedTraits;`

### `Plugins/Experimental/UAF/UAFTestSuites/Source/UAFAnimGraphTestSuite/Private/GCTestsUtil.h` (Private)


#### struct `FUAFTestAnimSequenceSharedData`  
`struct FUAFTestAnimSequenceSharedData : public FAnimNextTraitSharedData`  
_L15-33_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L20 _public member_ `TObjectPtr<UAnimSequence> AnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L25 _public member_ `EAnimInterpolationType DummyProp0 = EAnimInterpolationType::Linear;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Adding a UEnum here to test for false positives when validating trait stacks. This pin shouldn't ever require GC handling so let's test it *doesn't* generate an error.

#### struct `FRigUnit_AnimSequenceTest`  
`struct FRigUnit_AnimSequenceTest : public FRigUnit_AnimNextBase`  
_L36-48_
- reflection: `USTRUCT(meta = (DocumentationPolicy = "None"))`
- inherits: `FRigUnit_AnimNextBase`
- L40 _public prototype_ `RIGVM_METHOD() void Execute();`
- L44 _public member_ `TObjectPtr<UAnimSequence> AnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (Output))`
- L47 _public member_ `bool bCreated = false;` — `UPROPERTY()`

#### class `UGraphInstanceHolder`  
`class UGraphInstanceHolder : public UObject`  
_L51-59_
- reflection: `UCLASS()`
- inherits: `UObject`
- L56 _public member_ `TSharedPtr<FAnimNextGraphInstance> GraphInstance;`
- L58 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`

#### Free symbols / members of external scopes

- L27 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \`
