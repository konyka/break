# Plugins / NNEModelTests

- module root: `Plugins/Experimental/NNE/NNEModelTests/Source/NNEModelTests`
- headers: 3; symbols: 66
- symbol kinds: class=3, delegate=1, member=35, namespace=5, prototype=14, struct=8
- PrivateDependencyModuleNames: AssetRegistry, Engine, Json, NNE, RHI, RenderCore
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/NNE/NNEModelTests/Source/NNEModelTests/Private/NNEModelTestsJson.h` (Private)


#### struct `UE::NNEModelTests::FInput`  
`struct FInput`  
_L11-16_
- L13 _public member_ `FString Path;`
- L14 _public member_ `TArray<int32> Shape;`
- L15 _public member_ `FString Type;`

#### struct `UE::NNEModelTests::FRuntimeParameters`  
`struct FRuntimeParameters`  
_L18-25_
- L20 _public member_ `FString Interface;`
- L21 _public member_ `FString RuntimeName;`
- L22 _public member_ `double AbsoluteError;`
- L23 _public member_ `double RelativeError;`
- L24 _public member_ `FString SkipReason;`

#### struct `UE::NNEModelTests::FModelTestParameters`  
`struct FModelTestParameters`  
_L27-34_
- L29 _public member_ `FString TestName;`
- L30 _public member_ `FString ModelPath;`
- L31 _public member_ `TArray<FInput> Inputs;`
- L32 _public member_ `TArray<FString> Outputs;`
- L33 _public member_ `TArray<FRuntimeParameters> Runtimes;`

#### struct `UE::NNEModelTests::Private::FRequirements`  
`struct FRequirements : public FJsonSerializable`  
_L38-49_
- inherits: `FJsonSerializable`
- L40 _public member_ `TArray<FString> PlatformOr;`
- L41 _public member_ `FString NNEShaders;`
- L42 _public member_ `FString NPU;`

#### struct `UE::NNEModelTests::Private::FEnvironment`  
`struct FEnvironment : public FJsonSerializable`  
_L51-66_
- inherits: `FJsonSerializable`
- L53 _public member_ `FRequirements Requirements;`
- L54 _public member_ `FString Interface;`
- L55 _public member_ `FString Runtime;`
- L56 _public member_ `double RelativeTolerance;`
- L57 _public member_ `double AbsoluteTolerance;`

#### struct `UE::NNEModelTests::Private::FInput`  
`struct FInput : public FJsonSerializable`  
_L68-79_
- inherits: `FJsonSerializable`
- L70 _public member_ `TArray<int32> Shape;`
- L71 _public member_ `FString Type;`
- L72 _public member_ `FString Initializer;`

#### struct `UE::NNEModelTests::Private::FModelTest`  
`struct FModelTest : public FJsonSerializable`  
_L81-94_
- inherits: `FJsonSerializable`
- L83 _public member_ `FString Name;`
- L84 _public member_ `FString Model;`
- L85 _public member_ `TArray<FInput> Inputs;`
- L86 _public member_ `TArray<FEnvironment> Environments;`

#### struct `UE::NNEModelTests::Private::FModelTests`  
`struct FModelTests : public FJsonSerializable`  
_L96-103_
- inherits: `FJsonSerializable`
- L98 _public member_ `TArray<FModelTest> Tests;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEModelTests` (scope `UE`)
- L36 _namespace_ `namespace Private` (scope `UE::NNEModelTests`)

### `Plugins/Experimental/NNE/NNEModelTests/Source/NNEModelTests/Public/NNEModelTests.h` (Public)


#### class `UNNEModelTests`  
`class UNNEModelTests : public UObject`  
_L21-42_
- reflection: `UCLASS(BlueprintType, Category = "NNE")`
- inherits: `UObject`
- L26 _public prototype_ `bool InitializeFromFile(const FString& FilePath, TMap<FString, TArray<FString>>& AdditionalFiles, TMap<FString, TSet<FString>>& RuntimeFilters);`
- L27 _public prototype_ `bool GetFilteredModelTestParameters(TArray<UE::NNEModelTests::FModelTestParameters>& ModelTestParameters);`
- L30 _private prototype_ `FString GetBasePath();`
- L31 _private prototype_ `FString GetAbsoluteAssetPath(const FString& RelativeAssetPath);`
- L34 _public member_ `FString ReimportPath;`
- L38 _private member_ `FString ModelTestsDescription;` — `UPROPERTY()`
- L41 _private member_ `TArray<FSoftObjectPath> TestAssetReferences;` — `UPROPERTY()`

#### class `UNNEModelTestData`  
`class UNNEModelTestData : public UObject`  
_L45-59_
- reflection: `UCLASS(BlueprintType, Category = "NNE")`
- inherits: `UObject`
- L50 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L54 _public prototype_ `bool InitializeFromFile(const FString& FilePath);`
- L55 _public prototype_ `TConstArrayView64<uint8> GetData();`
- L58 _private member_ `TArray<uint8, TAlignedHeapAllocator<NNEMODELTESTS_TENSOR_DATA_ALIGNMENT>> Data;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNEModelTests, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNEModelTests, Log, All);`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace NNEModelTests` (scope `UE`)

### `Plugins/Experimental/NNE/NNEModelTests/Source/NNEModelTests/Public/NNEModelTestsModule.h` (Public)


#### class `FNNEModelTestsModule`  
`class FNNEModelTestsModule : public IModuleInterface`  
_L13-30_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `void ReloadModelTests();`
- L22 _public prototype_ `bool RunModelTests(int32& NumSuccesses, int32& NumSkipped, int32& Total);`
- L25 _private prototype_ `void OnAssetRegistryReady();`
- L26 _private prototype_ `bool LoadModelTests(TObjectPtr<UNNEModelTests> ModelTests);`
- L28 _private member_ `TMap<FString, TSharedPtr<FNNEModelTest>> ModelTestsMap;`
- L29 _private member_ `FDelegateHandle FilesLoadedHandle;`
