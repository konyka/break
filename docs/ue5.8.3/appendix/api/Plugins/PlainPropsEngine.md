# Plugins / PlainPropsEngine

- module root: `Plugins/Experimental/PlainPropsEngine/Source`
- headers: 7; symbols: 42
- symbol kinds: class=3, delegate=1, function=2, member=13, namespace=8, prototype=11, struct=4
- PrivateDependencyModuleNames: BlueprintGraph, Core, CorePreciseFP, CoreUObject, Engine, GameplayAbilities, Niagara, PlainProps, PlainPropsUObject, UnrealEd

### `Plugins/Experimental/PlainPropsEngine/Source/Private/PlainPropsEngineBindings.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlainPropsEngine, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlainPropsEngine, Log, All);`
- L8 _namespace_ `namespace PlainProps`
- L8 _namespace_ `namespace UE` (scope `PlainProps`)
- L12 _prototype_ `void CustomBindEngineTypes(EBindMode Mode);` (scope `PlainProps::UE`)
- L13 _prototype_ `void CustomBindAnimationTypes(EBindMode Mode);` (scope `PlainProps::UE`)
- L14 _prototype_ `void CustomBindNiagaraTypes(EBindMode Mode);` (scope `PlainProps::UE`)
- L15 _prototype_ `void CustomBindBlueprintTypes(EBindMode Mode);` (scope `PlainProps::UE`)

### `Plugins/Experimental/PlainPropsEngine/Source/Private/PlainPropsTestAssets.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PlainProps`
- L9 _namespace_ `namespace UE` (scope `PlainProps`)
- L12 _prototype_ `TArray<UObject*> CreateTestAssets();` (scope `PlainProps::UE`)

### `Plugins/Experimental/PlainPropsEngine/Source/Private/PlainPropsTestBindings.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PlainProps`
- L7 _namespace_ `namespace UE` (scope `PlainProps`)
- L12 _prototype_ `void CustomBindTestTypes(EBindMode Mode);` (scope `PlainProps::UE`)

### `Plugins/Experimental/PlainPropsEngine/Source/Public/PlainPropsCommandlets.h` (Public)


#### class `UTestPlainPropsCommandlet`  
`class UTestPlainPropsCommandlet : public UCommandlet`  
_L11-15_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- L14 _private prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Experimental/PlainPropsEngine/Source/Public/PlainPropsEngineModule.h` (Public)


#### class `FPlainPropsEngineModule`  
`class FPlainPropsEngineModule final : public IModuleInterface`  
_L7-11_
- inherits: `IModuleInterface`
- L9 _private prototype_ `virtual void StartupModule();`
- L10 _private prototype_ `virtual void ShutdownModule();`

### `Plugins/Experimental/PlainPropsEngine/Source/Public/PlainPropsEngineTestUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PlainProps`
- L7 _namespace_ `namespace UE` (scope `PlainProps`)
- L12 _prototype_ `void BindAllTypes(EBindMode Mode, EBatchType BatchType);` (scope `PlainProps::UE`)

### `Plugins/Experimental/PlainPropsEngine/Source/Public/PlainPropsTestTypes.h` (Public)


#### struct `FPlainPropsInstancedStructTestSchemaBase`  
`struct FPlainPropsInstancedStructTestSchemaBase`  
_L13-19_
- reflection: `USTRUCT()`
- L18 _public member_ `bool bValue = false;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### struct `FPlainPropsInstancedStructTestSchemaA`  
`struct FPlainPropsInstancedStructTestSchemaA : public FPlainPropsInstancedStructTestSchemaBase`  
_L22-34_
- reflection: `USTRUCT()`
- inherits: `FPlainPropsInstancedStructTestSchemaBase`
- L27 _public member_ `float X = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L30 _public member_ `float Y = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L33 _public member_ `float Z = 3.f;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### struct `FPlainPropsInstancedStructTestSchemaB`  
`struct FPlainPropsInstancedStructTestSchemaB : public FPlainPropsInstancedStructTestSchemaBase`  
_L37-46_
- reflection: `USTRUCT()`
- inherits: `FPlainPropsInstancedStructTestSchemaBase`
- L42 _public member_ `int32 Count = 4;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L45 _public member_ `FName Label = FName("Fiv` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### struct `FPlainPropsInstancedStructTestCustomBound`  
`struct FPlainPropsInstancedStructTestCustomBound : public FPlainPropsInstancedStructTestSchemaBase`  
_L49-61_
- reflection: `USTRUCT()`
- inherits: `FPlainPropsInstancedStructTestSchemaBase`
- L54 _public member_ `int32 Id = 6;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### class `UPlainPropsInstancedStructTestAsset`  
`class UPlainPropsInstancedStructTestAsset : public UDataAsset`  
_L65-109_
- reflection: `UCLASS()`
- inherits: `UDataAsset`
- desc: Test asset for exercising FInstancedStruct serialization through the PlainProps custom binding.
- L70 _public function_ `UPlainPropsInstancedStructTestAsset()`
- L88 _public member_ `FInstancedStruct StructA;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Single FInstancedStruct holding FPlainPropsInstancedStructTestSchemaA
- L92 _public member_ `FInstancedStruct StructB;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Single FInstancedStruct holding FPlainPropsInstancedStructTestSchemaB
- L96 _public member_ `FInstancedStruct StructC;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Single FInstancedStruct holding FPlainPropsInstancedStructTestCustomBound (with a custom binding)
- L100 _public member_ `TArray<FInstancedStruct> MixedArray;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Heterogeneous array: mix of FPlainPropsInstancedStructTestSchemaA, FPlainPropsInstancedStructTestSchemaB and FPlainPropsInstancedStructTestCustomBound entries
- L104 _public member_ `FInstancedStruct EmptyStruct;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Intentionally empty — exercises the null/empty case
- L108 _public member_ `TInstancedStruct<FPlainPropsInstancedStructTestSchemaBase> BaseStruct;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Single TInstancedStruct<FPlainPropsInstancedStructTestSchemaBase> holding FPlainPropsInstancedStructTestSchemaA

#### Free symbols / members of external scopes

- L57 _function_ `friend bool operator==(const FPlainPropsInstancedStructTestCustomBound& Lhs, const FPlainPropsInstancedStructTestCustomBound& Rhs)` — Used by custom binding
